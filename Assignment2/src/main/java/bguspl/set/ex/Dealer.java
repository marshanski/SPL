package bguspl.set.ex;
import java.util.*;
import bguspl.set.Env;
import java.util.Random;
import java.math.*;
import java.sql.Time;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;


/**
 * This class manages the dealer's threads and data
 */
public class Dealer implements Runnable {

    /**
     * The game environment object.
     */
    private final Env env;

    /**
     * Game entities.
     */
    private final Table table;
    private final Player[] players;
    private  int[] set;
    private final Thread playerThreads[];
    private static Object lock ;



    /**
     * The list of card ids that are left in the dealer's deck.
     */
    private final List<Integer> deck;
    private Deque<Integer> q;
    private ArrayBlockingQueue<Integer> queue;
    private Semaphore semaphore;


    /**
     * True iff game should be terminated due to an external event.
     */
    private volatile boolean terminate;
    private volatile boolean found;

    /**
     * The time when the dealer needs to reshuffle the deck due to turn timeout.
     */
    private long reshuffleTime = Long.MAX_VALUE;

    public Dealer(Env env, Table table, Player[] players) 
    {
        this.env           = env;
        this.table         = table;
        this.players       = players;
        deck               = IntStream.range(0, env.config.deckSize).boxed().collect(Collectors.toList());
        this.playerThreads = new Thread[this.players.length];
        this.lock          = new Object();
        this.q             = new LinkedList<Integer>();
        this.semaphore     = new Semaphore(4);
        this.set           = new int[this.env.config.featureSize];
        this.queue         = new ArrayBlockingQueue<>(this.players.length);
       
    }

    /**
     * The dealer thread starts here (main loop for the dealer thread).
     */
    @Override
    public void run() 
    {
        System.out.printf("Info: Thread %s starting.%n", Thread.currentThread().getName());
        this.stopPress();
        for(int i=0 ;i<this.players.length;i++)
        {
            this.playerThreads[i] = new Thread(this.players[i], "player"+ i);
            this.playerThreads[i].start();
        }
        placeCardsOnTable();
        while (!shouldFinish())
        {
            this.startPress();
            found = false;
            timerLoop();
            this.updateRound();
        }
        announceWinners();
        System.out.printf("Info: Thread %s terminated.%n", Thread.currentThread().getName());
    }


    public void updateRound()
    {
        try{Thread.currentThread().sleep(1000);}
        catch(Exception ex){}
        if(found)
        this.updateAfterSet(this.set);
        else
        {
            removeAllCardsFromTable();
            placeCardsOnTable();
        }

    }

    /**
     * The inner loop of the dealer thread that runs as long as the countdown did not time out.
     */
    private void timerLoop() 
    {
        this.env.ui.setCountdown(60999, terminate);
        long start    = System.currentTimeMillis();
        long end      = start + 60999;
        while (!terminate && !found && System.currentTimeMillis() < end) 
        {
            sleepUntilWokenOrTimeout();
            updateTimerDisplay(found,end);
        }
    }
    /**
     * Called when the game should be terminated due to an external event.
     */
    public void terminate() 
    {
        terminate = true;
        for(int i=0 ;i<this.players.length;i++)
        {
            this.players[i].terminate();
            try{this.playerThreads[i].join();}
            catch(Exception ex){}
                
        }
    }

    /**
     * Check if the game should be terminated or the game end conditions are met.
     *
     * @return true iff the game should be finished.
     */
    private boolean shouldFinish() 
    {
        return terminate || env.util.findSets(deck, 1).size() == 0;
    }

    /**
     * Checks if any cards should be removed from the table and returns them to the deck.
     */
    private void removeCardsFromTable() 
    {
        // TODO implement
    }

    /**
     * Check if any cards can be removed from the deck and placed on the table.
     */
    private void placeCardsOnTable() 
    {
        
        if(deck.size()>12)
        {
            int k;
            Random rand  = new Random();
            List<int[]> sets = this.env.util.findSets(deck,1);
            int[] a = sets.get(0);
            for(int i=0;i<3;i++)
            {
                this.table.placeCard(a[i],i);
                deck.remove(a[i]);
            }
            
            sets = this.env.util.findSets(deck,1);
            a          = sets.get(0);
            for(int i=0;i<3;i++)
            {
                this.table.placeCard(a[i],i+3);
                deck.remove(a[i]);
            }

            for(int i=6 ; i<12; i++)
            {
                k = rand.nextInt(deck.size());
                this.table.placeCard(deck.get(k),i);
                deck.remove(k);
            }
        }
    }



    /**
     * Sleep for a fixed amount of time or until the thread is awakened for some purpose.
     * @throws InterruptedException
     */
    private void sleepUntilWokenOrTimeout() 
    {
        long start     = System.currentTimeMillis();
        long time      = start;
        long toSleep   = 1000;
        while (time < start+1000 && !found)
        {
            synchronized (this.lock) 
            {
                try
                {
                    lock.wait(toSleep);
                    if(this.queue.size()>0)this.checkSet();
                    time    = System.currentTimeMillis();
                    toSleep = 1000-(time-start); 
                    
                }
                catch (InterruptedException ignored) {}
            }
        }
    }
    /**
     * Reset and/or update the countdown and the countdown display.
     */
    private void updateTimerDisplay(boolean reset,long end) 
    {
        this.env.ui.setCountdown(end-System.currentTimeMillis(), reset);
    }

    /**
     * Returns all the cards from the table to the deck.
     */
    private void removeAllCardsFromTable() 
    {
        for(int i=0;i<12;i++)
            removeCardToDeck(i);
    }
    /**
     * @param set
     * the set array represents the slots that needs to be replaced.
     */
    private void updateAfterSet(int[]set)//the set array represents the slots that needs to be removed.
    {
        this.table.removeSetFromTable(set);
        for(int i=0;i<set.length; i++)
        {
            this.placeACardInSlot(set[i]);
        }
    }

    /**
     * removes a card from the table, and return it to the deck.
     * @param slot
     */
    public void placeACardInSlot(int slot) // remove a card from the deck and place it in the slot
    {
        //make try and catch if there are no cards left in the deck!!!

        List<int[]> sets = this.env.util.findSets(deck,1);
        int[] a          = sets.get(0);
        for(int i=0;i<3;i++)
        {
            this.table.placeCard(a[i],i);
            deck.remove(a[i]);
        }

        /*Random rand = new Random();
        int k = rand.nextInt(deck.size());
        this.table.placeCard(deck.get(k),slot);
        deck.remove(k);*/
    }
    
     /**
     * removes a card from the table, and return it to the deck.
     * @param slot
     */
    public void removeCardToDeck(int slot)
    {
        try {
            Thread.sleep(env.config.tableDelayMillis);
        } catch (InterruptedException ignored) {}
        // do a try catch if is trying to remove a card that isnt on the table!!
        deck.add(table.slotToCard[slot]);
        this.table.removeCard(slot);
        this.env.ui.removeCard(slot);
    }
        
    /**
     * Check who is/are the winner/s and displays them.
     */
    private void announceWinners() 
    {
        // TODO implement
    }


    public void check(int k)
    {
        synchronized (this.queue)
        {
            this.addToQueue(k);
            synchronized (this.lock) {this.lock.notifyAll();}
            this.goWaitPlayer(k);
            this.pollToQueue();
        }
        
    }

    public void goWaitPlayer(int k)
    {
        try {synchronized (this.playerThreads[k]) { this.playerThreads[k].wait();}} 
        catch (InterruptedException ignored) {}
    }

    public void addToQueue(int k) 
    {
        synchronized (this.queue)
        {
            this.queue.add(k);
            this.queue.notifyAll();
        }
    }
    public void pollToQueue() 
    {
        synchronized (this.queue)
        {
            this.queue.poll();
            this.queue.notifyAll();
        }
    }


    public void checkSet()
    {
        int i  = this.queue.peek();
        int[] cards = new int[this.env.config.featureSize];
        int[] press = this.players[i].getPress();
        for(int k=0;k<cards.length;k++)
        {
            cards[k] = this.table.getSlotToCard(press[k]);
        }
        
        if(this.env.util.testSet(cards))
        {
            this.stopPress();
            this.set = press;
            found    = true;
            System.out.println("FOUND");//debug
            this.players[i].setAnswer(1);
            this.removeChecks();
        }
        else
        {
            this.players[i].setAnswer(-1);
        }
        
        synchronized (this.playerThreads[i]) { this.playerThreads[i].notifyAll();}

    }

    public void stopPress()
    {
        for(int i=0;i<this.players.length;i++)
        {
            this.players[i].stopPress();
        }
    }

    public void startPress()
    {
        for(int i=0;i<this.players.length;i++)
        {
            this.players[i].startPress();
        }
    }

    public void removeChecks()
    {
        Deque<Integer> c = new LinkedList<Integer>();
        boolean match;
        int[] press;
        int i;

        while(this.queue.size()>0)
        {
            c.add(this.queue.poll());
        }
        while(c.size()>0)
        {
            i     = c.removeFirst();
            press = this.players[i].getPress();
            match = false;
            for(int j=0;j<press.length;j++)
            {
                for(int k=0;k<set.length;k++)
                {
                    if(this.set[k]==press[j])match = true;
                }
            }
            if(!match)
                this.queue.add(i);
            else
                synchronized (this.playerThreads[i]) { this.playerThreads[i].notifyAll();}
        }

        

    }

    
}

package bguspl.set.ex;
import java.util.*;
import bguspl.set.Env;
import java.util.stream.IntStream;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.concurrent.ArrayBlockingQueue;



/**
 * This class manages the dealer's threads and data
 */
public class Dealer implements Runnable {

    /**
     * The game environment object.
     */
    private final Env env;
    private final int MARGIN = 999;
    private final int SECOND = 1000;

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
    private ArrayBlockingQueue<Integer> queue;

    /**
     * True iff game should be terminated due to an external event.
     */
    private volatile boolean terminate;
    private volatile boolean found;
    private volatile boolean thereIsNoSet;
    private volatile boolean stop;

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
        this.found         = false;
        this.thereIsNoSet  = false;
        this.set           = new int[this.env.config.featureSize];
        this.queue         = new ArrayBlockingQueue<>(this.players.length);
       
    }

    /**
     * The dealer thread starts here (main loop for the dealer thread).
     */
    @Override
    public void run() 
    {
        env.logger.info("Thread " + Thread.currentThread().getName() + " starting.");
        this.runPlayers();
        this.stopPress(); 
        this.debug();
        placeCardsOnTable();
        while (!shouldFinish())
        {
            this.startPress();
            this.found = false;
            this.table.hints();
            timerLoop();
            this.updateRound();
        }
        announceWinners();
        env.logger.info("Thread " + Thread.currentThread().getName() + " terminated.");
    }


    public void updateRound()
    {

        if(this.found)this.updateAfterSet(this.set);
        else
        {
            this.updateKeyPress(this.createSlots());
            removeAllCardsFromTable();
            placeCardsOnTable();
        }


    }

    public int[] createSlots()
    {
        int [] slots = new int[this.env.config.tableSize];
        for(int i=0;i<slots.length;i++)slots[i]=i;
        return slots;

    }

    /**
     * The inner loop of the dealer thread that runs as long as the countdown did not time out.
     */
    private void timerLoop() 
    {
        this.env.ui.setCountdown(this.env.config.turnTimeoutMillis, terminate);
        long start    = System.currentTimeMillis();
        long end      = start +this.env.config.turnTimeoutMillis+MARGIN;
        while (!terminate && !this.found && System.currentTimeMillis() < end) 
        {
            sleepUntilWokenOrTimeout();
            updateTimerDisplay(this.found,end);
        }
        
    }
    /**
     * Called when the game should be terminated due to an external event.
     */
    public void terminate() 
    {
        terminate = true;  
        this.stopPress();
        this.shutDownPlayers();
    }


    public void checkPossibleSet()
    {
        ArrayList<Integer> table = new ArrayList<Integer>();
        Integer [] slot =this.table.getSlotToCard();
        for(int i=0;i<slot.length;i++)
        {
            if(slot[i] != null)
                table.add(slot[i]);
        }
        this.thereIsNoSet = (env.util.findSets(deck, 1).size() == 0 && env.util.findSets(table, 1).size() == 0) ;
    }


    /**
     * Check if the game should be terminated or the game end conditions are met.
     *
     * @return true iff the game should be finished.
     */
    private boolean shouldFinish() 
    {
        return terminate || this.thereIsNoSet;
    
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
        int k,size;
        Random rand  = new Random();
        this.checkPossibleSet();
        if(deck.size()>this.env.config.tableSize)
            size =this.env.config.tableSize;
        else
            size = deck.size();

        for(int i=0 ; i<size; i++)
        {
            k = rand.nextInt(deck.size());
            this.table.placeCard(deck.get(k),i);
            deck.remove(k);
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
        long toSleep   = 10;
        while (time < start+SECOND && !found)
        {
            synchronized (this.lock) 
            {
                try
                {
                    lock.wait(toSleep);
                    if(this.queue.size()>0)this.checkSet();
                    time    = System.currentTimeMillis();
                    toSleep = SECOND-(time-start); 
                    
                    
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

    public void debug()
    {
        int k;
        Random rand  = new Random();
 
        for(int i=0 ; i<60; i++)
        {
            k = rand.nextInt(deck.size());
            deck.remove(k);
        }

    }

    /**
     * Returns all the cards from the table to the deck.
     */
    private void removeAllCardsFromTable() 
    {
        for(int i=0;i<this.env.config.tableSize;i++)
            removeCardToDeck(i);
    }
    /**
     * @param set
     * the set array represents the slots that needs to be replaced.
     */

    private void updateAfterSet(int[]set)//the set array represents the slots that needs to be removed.
    {
        this.stopPress();
        this.table.removeSetFromTable(set);
        this.updateKeyPress(set);
        this.checkPossibleSet();
        for(int i=0;i<set.length; i++)this.placeACardInSlot(set[i]);
    }

    private void updateKeyPress(int[]slots)
    {
        int [] keyPress;
        int currentPress,changes;
        for(int i=0;i<this.players.length;i++)
        {
            if(this.players[i].isHuman())
            {
                keyPress     = this.players[i].getPress();
                currentPress = this.players[i].getCurrentPress();
                changes      = 0;
                for(int k=0;k<slots.length;k++)
                {
                    for(int j=0;j<currentPress;j++)
                    {
                        if(keyPress[j]==slots[k])
                        {
                            changes++;
                            keyPress[j] = 100;

                        }
                    }
                }
                if(changes>0)
                {
                    currentPress -=changes;
                    for (int r = 0;r<keyPress.length;r++)
                    {
                        if(keyPress[r]==100)keyPress[r]=-1;
                    }
                    Arrays.sort(keyPress);
                    for(int r=0;r<keyPress.length;r++)keyPress[r]=keyPress[r]*-1;
                    Arrays.sort(keyPress);
                    for(int r=0;r<keyPress.length;r++)keyPress[r]=keyPress[r]*-1;
                }
                this.players[i].setCheck();
                this.players[i].setPress(keyPress);
                this.players[i].setCurrentPress(currentPress);
                
            }
        }
    }


    /**
     * removes a card from the table, and return it to the deck.
     * @param slot
     */
    public void placeACardInSlot(int slot) // remove a card from the deck and place it in the slot
    {
        //make try and catch if there are no cards left in the deck!!!
        Random rand = new Random();
        if(deck.size()>0)
        {
            int k = rand.nextInt(deck.size());
            this.table.placeCard(deck.get(k),slot);
            deck.remove(k);
        }
    }
    
     /**
     * removes a card from the table, and return it to the deck.
     * @param slot
     */
    public void removeCardToDeck(int slot)
    {

        deck.add(table.slotToCard[slot]);
        this.table.removeCard(slot);
        //this.env.ui.removeCard(slot);
        for(int i=0;i<this.players.length;i++)
        {
            this.table.removeToken(this.players[i].getId(), slot);
            //this.env.ui.removeToken(this.players[i].getId(),slot);
        }
    }
        
    /**
     * Check who is/are the winner/s and displays them.
     */
    private void announceWinners() 
    {

        if(!terminate)
        {
            //terminate = true;
            
            this.removeAllCardsFromTable();
            this.env.ui.announceWinner(this.findWinners());
        }
        this.shutDownPlayers();


    }

    public int[] findWinners()
    {
        int max =this.players[0].getScore(),mone=0,k=0;
        int [] score;
        for (int i=1;i<this.players.length;i++)
        {
            if(this.players[i].getScore()>max)
                max = this.players[i].getScore();
        }
        for (int i=0;i<this.players.length;i++)
        {
            if(this.players[i].getScore()==max)
                mone++;
        }
        score = new int[mone];
        k=0;
        for (int i=0;i<this.players.length;i++)
        {
            if(this.players[i].getScore()==max)
            {
                score[k]=this.players[i].getId();
                k++;
            }
        }
        return score;
    }

    public void check(int k)
    {
        synchronized (this.queue)
        {
            this.addToQueue(k);
            //while(this.queue.size()>0 && this.queue.peek() !=k)
                
            synchronized (this.lock) {this.lock.notifyAll();}
            this.goWaitPlayer(k);
            this.pollToQueue(k);
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
    public void pollToQueue(int k) 
    {
        synchronized (this.queue)
        {
            if(this.queue.size()>0 && this.queue.peek() ==k)
                this.queue.poll();
            this.queue.notifyAll();
        }
    }

    public void checkSet()
    {
        if(!found)
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
                this.set = Arrays.copyOf(press,press.length);
                this.players[i].setAnswer(1);
                this.removeChecks();
                this.found    = true;
            }
            else
            {
                this.players[i].setAnswer(-1);
            }
            
            synchronized (this.playerThreads[i]) { this.playerThreads[i].notifyAll();}
        }

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

    public void runPlayers()
    {
        for(int i=0 ;i<this.players.length;i++)
        {
            this.playerThreads[i] = new Thread(this.players[i], "player"+ i);
            this.playerThreads[i].start();
        }
    }

    public void shutDownPlayers()
    {
        for(int i=this.players.length-1 ;i>=0;i--)
        {
            this.players[i].terminate();
            try{this.playerThreads[i].join();}
            catch(Exception ex){}
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
                this.addToQueue(i);
            else
                synchronized (this.playerThreads[i]) { this.playerThreads[i].notifyAll();}
        }

    }

    
}

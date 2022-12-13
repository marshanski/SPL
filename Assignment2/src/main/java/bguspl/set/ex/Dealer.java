package bguspl.set.ex;

import bguspl.set.Env;
import java.util.Random;
import java.math.*;
import java.sql.Time;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

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
    private final Thread playerThreads[];
    private static Object lock ;


    /**
     * The list of card ids that are left in the dealer's deck.
     */
    private final List<Integer> deck;

    /**
     * True iff game should be terminated due to an external event.
     */
    private volatile boolean terminate;

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
        
    }

    /**
     * The dealer thread starts here (main loop for the dealer thread).
     */
    @Override
    public void run() 
    {
        System.out.printf("Info: Thread %s starting.%n", Thread.currentThread().getName());
        int k =0 ;
        boolean found = false;
        

        for(int i=0 ;i<this.players.length;i++)
        {
            this.playerThreads[i] = new Thread(this.players[i], "player"+ i);
            this.playerThreads[i].start();
        }
        while (!shouldFinish())
        {
            placeCardsOnTable(found);
            timerLoop(found);
            //updateTimerDisplay(false);
            removeAllCardsFromTable();
            k++;
        }
        announceWinners();
        System.out.printf("Info: Thread %s terminated.%n", Thread.currentThread().getName());
    }

    /**
     * The inner loop of the dealer thread that runs as long as the countdown did not time out.
     */
    private void timerLoop(boolean found) 
    {
        int i=0;
        this.env.ui.setCountdown(60000, terminate);
        long start    = System.currentTimeMillis();
        long end      = start + 60000;
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
    private void placeCardsOnTable(boolean found) 
    {
        if (!found)
        {
            int k;
            Random rand  = new Random();
            for(int i=0 ; i<12; i++)
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
        while (time < start+1000)
        {
            synchronized (this.lock) 
            {
                try
                {
                    lock.wait(toSleep);
                    if(System.currentTimeMillis()<start+1000){System.out.println("WIWI");}
                    time    = System.currentTimeMillis();
                    toSleep = 1000-(time-start); 
                    
                }
                catch (InterruptedException ignored) 
                {
                    //System.out.println("WIWI");
                    
                }
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
    }
        
    /**
     * Check who is/are the winner/s and displays them.
     */
    private void announceWinners() 
    {
        // TODO implement
    }

    public void check()
    {
        synchronized (this.lock) 
        {
            this.lock.notifyAll();
        }

    }
    

    
}

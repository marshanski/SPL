
package bguspl.set.ex;
import java.util.Arrays;
import bguspl.set.Env;

/**
 * This class manages the players' threads and data
 *
 * @inv id >= 0
 * @inv score >= 0
 */
public class Player implements Runnable {

    /**
     * The game environment object.
     */
    private final Env env;

    /**
     * Game entities.
     */
    private final Table table;

    /**
     * The id of the player (starting from 0).
     */
    public final int id;

    /**
     * The thread representing the current player.
     */
    private Thread playerThread;

    /**
     * The thread of the AI (computer) player (an additional thread used to generate key presses).
     */
    private Thread aiThread;
    private Dealer dealer;
    private int[] keyPresses;

    /**
     * this erplaces 'null' in the keyPresses array.
     */
    private final int noPress = -1;

    /**
     * the number of preeses currenlty in keyPresses array.
     */
    private int currPresses = 0;
    /**
     * True iff the player is human (not a computer player).
     */
    private final boolean human;

    /**
     * True iff game should be terminated due to an external event.
     */
    private volatile boolean terminate;
    private volatile boolean found;
    private volatile boolean check;

    /**
     * The current score of the player.
     */
    private int score;

    /**
     * The class constructor.
     *
     * @param env    - the environment object.
     * @param dealer - the dealer object.
     * @param table  - the table object.
     * @param id     - the id of the player.
     * @param human  - true iff the player is a human player (i.e. input is provided manually, via the keyboard).
     */
    public Player(Env env, Dealer dealer, Table table, int id, boolean human) 
    {
        this.env    = env;
        this.table  = table;
        this.id     = id;
        this.human  = human;
        this.dealer = dealer;
        this.keyPresses = new int[this.env.config.featureSize];
        this.score  = 0;
        for (int i=0;i<this.keyPresses.length;i++)
        {
            keyPresses[i]= noPress;
        }
        found = true;
        check = false;
    }

    /**
     * The main player thread of each player starts here (main loop for the player thread).
     */
    @Override
    public void run() 
    {
        playerThread = Thread.currentThread();
        System.out.printf("Info: Thread %s starting.%n", Thread.currentThread().getName());
        if (!human) createArtificialIntelligence();
        while (!terminate) 
        {
            
        }

        if (!human) 
        {
            try 
            {
                aiThread.interrupt();
                aiThread.join(); 
            } 
            catch (InterruptedException ignored) {}
        }
        System.out.printf("Info: Thread %s terminated.%n", Thread.currentThread().getName());
    }

    /**
     * Creates an additional thread for an AI (computer) player. The main loop of this thread repeatedly generates
     * key presses. If the queue of key presses is full, the thread waits until it is not full.
     */
    private void createArtificialIntelligence() {
        // note: this is a very very smart AI (!)
        aiThread = new Thread(() -> {
            System.out.printf("Info: Thread %s starting.%n", Thread.currentThread().getName());
            while (!terminate) 
            {
                // TODO implement player key press simulator
                try 
                {
                    synchronized (this) { wait();}
                } 
                catch (InterruptedException ignored) 
                {
                    this.terminate();
                }
            }
            System.out.printf("Info: Thread %s terminated.%n", Thread.currentThread().getName());
        }, "computer-" + id);
        aiThread.start();
    }

    /**
     * Called when the game should be terminated due to an external event.
     */
    public void terminate() 
    {
        terminate = true;
    }
    public void stopPress() 
    {
        found = true;
    }
    public void startPress() 
    {
        found = false;
    }

    /**
     * This method is called when a key is pressed.
     *
     * @param slot - the slot corresponding to the key pressed.
     */
    public void keyPressed(int slot) 
    {
        System.out.println(slot);
        if(currPresses <= keyPresses.length-1 && !found && !check)
        {
            int slotIndex = -1;
            for(int i=0;i<= currPresses;i++)
            {
                if(keyPresses[i] == slot)
                    slotIndex =i;
            }

            if(slotIndex < 0) //the player preesed a new key
            {
                this.env.ui.placeToken(id, slot);
                keyPresses[currPresses] = slot;
                currPresses++;
                if(currPresses ==3)
                {
                    check = true;
                    this.dealer.check(this.id);
                    
                }
            }
            else //the player pressed an existing key, meaning we need to delete.
            {
                keyPresses[slotIndex] = noPress;
                currPresses--;
                this.env.ui.removeToken(id, slot);
            }

        }
    }

    /**
     * Award a point to a player and perform other related actions.
     *
     * @post - the player's score is increased by 1.
     * @post - the player's score is updated in the ui.
     */
    public void point() 
    {
        // TODO implement

        int ignored = table.countCards(); 
        this.score ++;// this part is just for demonstration in the unit tests
        env.ui.setScore(id, this.score);
    }

    /**
     * Penalize a player and perform other related actions.
     */
  
    public void penalty(int penaltyTime) 
        {
            // TODO implement
            try{
                Thread.sleep(penaltyTime);
            }
            catch (InterruptedException e) {
                // handle the InterruptedException
                System.out.println("The thread was interrupted: " + e.getMessage());
            }
        }

    public int getScore() 
    {
        return score;
    }
    public int[] getPress()
    {
        return this.keyPresses;
    }
}
package bguspl.set.ex;
import java.util.Arrays;
import bguspl.set.Env;
import java.util.*;

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
    private final int noPress   = -1;
    private final int AIWAIT    = 10;
    private final int ONESECOND = 950;

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
    private volatile boolean freeze;
    private int answer;
    private static Object currentPresslock ;

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
        this.env        = env;
        this.table      = table;
        this.id         = id;
        this.human      = human;
        this.dealer     = dealer;
        this.keyPresses = new int[this.env.config.featureSize];
        this.currentPresslock = new Object();
        this.score      = 0;
        this.answer     = 0;
        this.initKeyPress();

        found = true;
        check = false;
        freeze =false;
    }

    /**
     * The main player thread of each player starts here (main loop for the player thread).
     */
    @Override
    public void run() 
    {
        playerThread = Thread.currentThread();
        env.logger.info("Thread " + Thread.currentThread().getName() + " starting.");
        if (!human) createArtificialIntelligence();
        while (!terminate) 
        {

        }
        if (!human) try {aiThread.interrupt(); aiThread.join(); } catch (InterruptedException ignored) {}
        env.logger.info("Thread " + Thread.currentThread().getName() + " terminated.");
    }
    

    public boolean isHuman()
    {
        return this.human;
    }

    public void initKeyPress()
    {
        for (int i=0;i<this.keyPresses.length;i++)
        {
            this.keyPresses[i]= noPress;
        }

    }

    /**
     * Creates an additional thread for an AI (computer) player. The main loop of this thread repeatedly generates
     * key presses. If the queue of key presses is full, the thread waits until it is not full.
     */
    private void createArtificialIntelligence() {
        // note: this is a very very smart AI (!)
        aiThread = new Thread(() -> {
            env.logger.info("Thread " + Thread.currentThread().getName() + " starting.");

            while (!terminate) 
            {
                this.keyPressAi();
                try {
                    synchronized (this) { wait(AIWAIT); }
                } catch (InterruptedException ignored) {this.terminate();}
            }
            env.logger.info("Thread " + Thread.currentThread().getName() + " terminated.");
        }, "computer-" + id);
        aiThread.start();
    }


    /**
     * This method is called when a key is pressed.
     *
     * @param slot - the slot corresponding to the key pressed.
     * @throws InterruptedException
     */
    public void keyPressed(int slot) 
    {
        System.out.println(slot);
        boolean betweenSet = false;
        while(found && !terminate)
        {
            if(this.dealer.inSet(slot))betweenSet = true;
        }
        if( !found && !freeze && isHuman() && this.table.getSlotToCard(slot)!=-1 && !betweenSet)
        {
            synchronized(this.currentPresslock)
            {

                int slotIndex = noPress;
                for(int i=0; i < this.currPresses; i++)
                {
                    if(this.keyPresses[i] == slot)
                        slotIndex =i;
                }
                if(check)//the player was already checked
                {
                    if(slotIndex < 0)
                    {
                        System.out.println("you cannot place another token until you take one out!");
                    }
                    else
                    {
                        this.removePress(slotIndex,slot);
                        check = false;
                    }
                }
                else// the player wasnt checked
                {
                    if(slotIndex < 0)
                    {
                        this.addPress(slot);
                    }
                    else
                    {
                        this.removePress(slotIndex,slot);

                    }
                }
                if(currPresses ==this.env.config.featureSize && !check)
                {
                    this.dealer.check(this.id);
                    freeze = true;
                    if(this.answer == -1)
                    {
                        
                        this.executeFreeze(this.env.config.penaltyFreezeMillis);
                        check = true;

                    }   
                    if(this.answer==1)
                    {
                        this.point();
                        this.executeFreeze(this.env.config.pointFreezeMillis);
                        check = true;
                    }
                
                }
                this.currentPresslock.notifyAll();
            }
            
        }

    }

    public void keyPressAi()
    {
        if(!found && !isHuman())
        {
            ArrayList<Integer> slots = this.table.getSlotsOnTable();
            Collections.shuffle(slots);
            
            for(int i=0;i<this.keyPresses.length;i++)
            {
                this.keyPresses[i]=slots.get(i);
                this.table.placeToken(this.id, slots.get(i)); 

            }

            this.currPresses=this.env.config.featureSize;
            this.dealer.check(this.id);
            if(answer ==1)
            {
                this.point();
                this.executeFreezeAI(this.env.config.pointFreezeMillis);
                //this.executeFreezeAI(1999);
            }
            else
            {
                this.executeFreezeAI(this.env.config.penaltyFreezeMillis);
                //this.executeFreezeAI(3999);
                for(int i=0;i<this.keyPresses.length;i++)
                {
                    this.table.removeToken(this.id, keyPresses[i]);

                }
            }
        }
    }
    public void descandingSort()
    {
        for(int i=0;i<this.keyPresses.length;i++)
        {
            if(this.keyPresses[i] == noPress)
                this.keyPresses[i] = 100;
        }
        Arrays.sort(this.keyPresses);
        for (int r = 0;r<this.keyPresses.length;r++)
        {
            if(this.keyPresses[r]==100)this.keyPresses[r]=-1;
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
        int ignored = table.countCards(); 
        this.score ++;// this part is just for demonstration in the unit tests
        env.ui.setScore(id, this.score);
    }

    public void addPress(int slot)
    {

        this.keyPresses[this.currPresses] = slot;
        this.currPresses++;
        this.table.placeToken(this.id, slot);

    }

    public void removePress(int slotIndex,int slot)
    {

        this.keyPresses[slotIndex] = noPress;
        this.currPresses--;
        this.table.removeToken(this.id, slot);
        this.descandingSort();
    }


    public int getScore() 
    {
        return score;
    }
    public int[] getPress()
    {
        return this.keyPresses;
    }

    public void executeFreeze(long penaltyTime)
    {
        if(!terminate)
        {
            Thread f = new Thread(() ->{this.freeze(penaltyTime);});
            f.start();
        }
    }

    public void executeFreezeAI(long penaltyTime)
    {
        this.freeze(penaltyTime);
    }


    public void freeze(long penaltyTime)
    {
        long start    = System.currentTimeMillis();
        long end      = start + penaltyTime;
        this.updateTimerDisplay(end);
        while (System.currentTimeMillis() < end && !terminate) 
        {
            synchronized (this) 
            {
                try
                {
                    this.wait(ONESECOND);
                    this.updateTimerDisplay(end);

                }
                catch (InterruptedException ignored) {}
            }
        }
        freeze =false;
    }

    private void updateTimerDisplay(long end) 
    {

        this.env.ui.setFreeze(this.id,end-System.currentTimeMillis());
    }

    public void setAnswer(int i)
    {
        this.answer = i;
    }
    
    public int getId()
    {
        return this.id;
    }

    public void setPress(int[]c)
    {
        this.keyPresses = c;
    }
    public void setCurrentPress(int l)
    {
        this.currPresses = l;
    }
    public int getCurrentPress()
    {
        return this.currPresses;
    }
    public void setCheck()
    {
        check = false;
    }
    public void terminate() 
    {
        terminate = true;
    }
    public void stopPress() 
    {
        found = true;

    }
    public boolean getFound()
    {
        return found;

    }
    public void startPress() 
    {
        found = false;
    }
    public int score()
    {
        return score;
    }

}
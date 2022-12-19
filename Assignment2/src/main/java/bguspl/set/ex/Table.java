package bguspl.set.ex;
import java.util.*;
import bguspl.set.Env;
import java.util.Random;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

/**
 * This class contains the data that is visible to the player.
 *
 * @inv slotToCard[x] == y iff cardToSlot[y] == x
 */
public class Table {

    /**
     * The game environment object.
     */
    private final Env env;

    /**
     * Mapping between a slot and the card placed in it (null if none).
     */
    protected final Integer[] slotToCard; // card per slot (if any)

    /**
     * Mapping between a card and the slot it is in (null if none).
     */
    protected final Integer[] cardToSlot; // slot per card (if any)

    /**
     * Mapping between a slot and the players that are placeing a token on that slot.
     */
    protected boolean[][] slotToPlayers; // slot per card (if any)

    /**
     * Constructor for testing.
     *
     * @param env        - the game environment objects.
     * @param slotToCard - mapping between a slot and the card placed in it (null if none).
     * @param cardToSlot - mapping between a card and the slot it is in (null if none).
     */
    public Table(Env env, Integer[] slotToCard, Integer[] cardToSlot) 
    {

        this.env        = env;
        this.slotToCard = slotToCard;
        this.cardToSlot = cardToSlot;
        this.slotToPlayers = new boolean[this.env.config.players][this.env.config.tableSize];
        this.initslotToPlayers();

    }

    /**
     * Constructor for actual usage.
     *
     * @param env - the game environment objects.
     */
    public Table(Env env) 
    {
        this(env, new Integer[env.config.tableSize], new Integer[env.config.deckSize]);
    }

    public void initslotToPlayers()
    {
        for(int i=0;i<this.slotToPlayers.length;i++)
        {
            for(int k=0;k<this.slotToPlayers[0].length;k++)
            {
                this.slotToPlayers[i][k] = false;
            }
        }

    }

    /**
     * This method prints all possible legal sets of cards that are currently on the table.
     */
    public void hints() {
        List<Integer> deck = Arrays.stream(slotToCard).filter(Objects::nonNull).collect(Collectors.toList());
        env.util.findSets(deck, Integer.MAX_VALUE).forEach(set -> {
            StringBuilder sb = new StringBuilder().append("Hint: Set found: ");
            List<Integer> slots = Arrays.stream(set).mapToObj(card -> cardToSlot[card]).sorted().collect(Collectors.toList());
            int[][] features = env.util.cardsToFeatures(set);
            System.out.println(sb.append("slots: ").append(slots).append(" features: ").append(Arrays.deepToString(features)));
        });
    }

    /**
     * Count the number of cards currently on the table.
     *
     * @return - the number of cards on the table.
     */
    public int countCards() 
    {
        int cards = 0;
        for (Integer card : slotToCard)
            if (card != null)
                ++cards;
        return cards;
    }


    /**
     * Places a card on the table in a grid slot.
     * @param card - the card id to place in the slot.
     * @param slot - the slot in which the card should be placed.
     *
     * @post - the card placed is on the table, in the assigned slot.
     */
    public void placeCard(int card, int slot) {
        try {
            Thread.sleep(env.config.tableDelayMillis);
        } catch (InterruptedException ignored) {}

        cardToSlot[card] = slot;
        slotToCard[slot] = card;
        this.env.ui.placeCard(card,slot);

    }
    public Integer[] getSlotToCard()
    {
        return Arrays.copyOf(this.slotToCard,this.slotToCard.length);
    }

    /**
     * Removes a card from a grid slot on the table.
     * @param slot - the slot from which to remove the card.
     */
    public void removeCard(int slot) {
        try {
            Thread.sleep(env.config.tableDelayMillis);
        } catch (InterruptedException ignored) {}

        this.slotToCard[slot] = null;
        this.env.ui.removeCard(slot);
    }

    /**
     * Places a player token on a grid slot.
     * @param player - the player the token belongs to.
     * @param slot   - the slot on which to place the token.
     */
    public void placeToken(int player, int slot) 
    {
    
        this.slotToPlayers[player][slot] = true;
        this.env.ui.placeToken(player, slot);
    }

    /**
     * Removes a token of a player from a grid slot.
     * @param player - the player the token belongs to.
     * @param slot   - the slot from which to remove the token.
     * @return       - true iff a token was successfully removed.
     */
    public boolean removeToken(int player, int slot) 
    {
        // TODO implement
        this.slotToPlayers[player][slot] = false;
        this.env.ui.removeToken(player, slot);
        return false;
    }

    public int getSlotToCard(int slot)
    {
        if(this.slotToCard[slot] ==null)
            return -1;
        return this.slotToCard[slot];
    }
    public int getCardToslot(int card)
    {
        return this.cardToSlot[card];
    }

    protected void removeSetFromTable(int[] set)
    {  
        for(int i=0; i<slotToPlayers.length;i++)// remove all token from the cards that made the set
        {
            for(int k=0;k<set.length;k++)
            {
                this.removeToken(i, set[k]);
                //this.env.ui.removeToken(i, set[k]);
            }
        }
        for(int k=0;k<set.length;k++)//remove the cards that made the set
        {
            this.removeCard(set[k]);
        }
        
    }

    public ArrayList<Integer> getSlotsOnTable()
    {
        ArrayList<Integer> slots = new ArrayList<Integer>();
        for(int i=0;i<this.env.config.tableSize;i++)
        {
            if(this.getSlotToCard(i)!=-1)
                slots.add(i);
        }
        return slots;
    }
}

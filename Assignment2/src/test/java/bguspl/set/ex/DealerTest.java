package bguspl.set.ex;

import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;
import bguspl.set.Config;
import bguspl.set.Env;
import bguspl.set.UserInterface;
import bguspl.set.Util;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.logging.Logger;

import javax.management.loading.PrivateMLet;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.ArgumentMatchers.eq;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

@ExtendWith(MockitoExtension.class)
public class DealerTest 
{

    Dealer dealer;

    @Mock
    Util util;

    @Mock 
    private UserInterface ui;

    @Mock
    private Table table;

    @Mock
    private Logger logger;


    @BeforeEach
    void setUp() 
    {
        // purposely do not find the configuration files (use defaults here).
        Env env = new Env(logger, new Config(logger, (String) null), ui, util);
        Player[] players = new Player[env.config.players];
        dealer = new Dealer(env, table, players);
        
    }

    @Test
    void shouldFinish()
    {
        boolean expectedTerminate    = false;
        boolean expectedThereIsNoSet = false; 
        boolean expectedResult = expectedTerminate || expectedThereIsNoSet;
        assertEquals(dealer.shouldFinish(), expectedResult);
    }

    @Test
    void getQueueSize()
    {
        int SizeBeforeAddition = dealer.getQueueSize();
        int expectedSizeAfterAddition = SizeBeforeAddition + 1;
        dealer.addToQueue(0);
        int sizeAfterAdd = dealer.getQueueSize();

        assertEquals(expectedSizeAfterAddition,sizeAfterAdd);

    }

}
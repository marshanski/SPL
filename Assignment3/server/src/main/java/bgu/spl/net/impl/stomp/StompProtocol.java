package bgu.spl.net.impl.stomp;

import bgu.spl.net.srv.Connections;
import bgu.spl.net.api.StompMessagingProtocol;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;

public class StompProtocol implements StompMessagingProtocol<String> {

    private int connectionId;
    private Connections<String> connections;
    private boolean shouldTerminate = false;
    private StompFrame stompFrame;
    private StompCommand stompCommand;
    private StompHeader stompHeader;
    //private Map<StompCommand, StompClass> commandToActions = new HashMap<>();


    @Override
    public void start(int connectionId, Connections<String> connections)
    {
        this.connectionId = connectionId;
        this.connections  = connections;
    }

    @Override
    public void process(String msg) 
    {
       stompFrame = StompFrame.fromString(msg);
       stompCommand = stompFrame.getCommand();
       switch(stompCommand)
       {
        case CONNECT:
            FrameConnect connectFrame = new FrameConnect(stompFrame);
            // activate connecy frame action method.

        case DISCONNECT:
            FrameDisconnect disconnectFrame = new FrameDisconnect(stompFrame);
            // activate connecy frame action method.
        case SEND:
            FrameSend sendFrame = new FrameSend(stompFrame);
            // activate connecy frame action method.
        case SUBSCRIBE:
            FrameSubscribe subscribeFrame = new FrameSubscribe(stompFrame);
            // activate connecy frame action method.
        case UNSUBSCRIBE:
            FrameUsubscribe unsubscribeFrame = new FrameUsubscribe(stompFrame);
            // activate connecy frame action method.
        


       }
       






    
    }

    @Override
    public boolean shouldTerminate() 
    {
        return shouldTerminate;
    }
    public void executeConnect(FrameConnect frame)
    {
        
        

    }

}
/*
 * עשות מחלקה לכל פריים בנפרד בתיקייה סטומפ.
לכתוב פה את הפעולות שמבצעות את כל הדברים בכל פריימ
בפעולה פרוסס יהיה סוויצ׳ קייס על הערך של הקומנד והוא יקרא לכל אחת מהפעולות האלה בהתאם לקומנד שהתקבל.
 * sholud have a strat function
 */
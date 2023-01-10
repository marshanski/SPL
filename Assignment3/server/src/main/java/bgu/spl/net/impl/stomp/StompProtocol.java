package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessagingProtocol;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;

public class StompProtocol implements MessagingProtocol<String> {

    private boolean shouldTerminate = false;
    private StompFrame stompFrame;
    private StompCommand stompCommand;
    private StompHeader stompHeader;
    //private Map<StompCommand, StompClass> commandToActions = new HashMap<>();

    @Override
    public String process(String msg) 
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
       






        shouldTerminate = "bye".equals(msg);
        System.out.println("[" + LocalDateTime.now() + "]: " + msg);
        return "hi";
    }

    @Override
    public boolean shouldTerminate() 
    {
        return shouldTerminate;
    }
    public void contentActions(FrameConnect frame)
    {


    }

}/*
לכתוב פה את הפעולות שמבצעות את כל הדברים בכל פריימ
בפעולה פרוסס יהיה סוויצ׳ קייס על הערך של הקומנד והוא יקרא לכל אחת מהפעולות האלה בהתאם לקומנד שהתקבל.
*/

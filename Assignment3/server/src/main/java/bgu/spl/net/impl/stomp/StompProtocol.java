package bgu.spl.net.impl.stomp;

import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.api.StompMessagingProtocol;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;

public class StompProtocol<T> implements StompMessagingProtocol<String> {

    private int connectionId;
    private ConnectionsImpl<String> connections;
    private boolean shouldTerminate = false;
    private StompFrame stompFrame;
    private StompCommand stompCommand;
    private StompHeader stompHeader;
    //private Map<StompCommand, StompClass> commandToActions = new HashMap<>();


    @Override
    public void start(int connectionId, ConnectionsImpl<String> connections)
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
            executeConnect(stompFrame);
            break;
        case DISCONNECT:
            FrameDisconnect disconnectFrame = new FrameDisconnect(stompFrame);
            executeDisconnect(stompFrame);
            break;
        case SEND:
            FrameSend sendFrame = new FrameSend(stompFrame);
            executeSend(stompFrame,msg);
            break;
        case SUBSCRIBE:
            FrameSubscribe subscribeFrame = new FrameSubscribe(stompFrame);
            executeSubscrice(stompFrame);
            break;
        case UNSUBSCRIBE:
            FrameUsubscribe unsubscribeFrame = new FrameUsubscribe(stompFrame);
            executeUnsubscribe(stompFrame);
            break;
        default:
            break;

       }
       
    }

    @Override
    public boolean shouldTerminate() 
    {
        return shouldTerminate;
    }

    public boolean containsReceipt(StompFrame frame)
    {
        if(frame.getHeaders().containsKey("receipt"))
            return true;
        return false;
    }
    
    public void executeConnect(StompFrame frame)
    {
        if(connections.connect(connectionId, frame.getHeaders().get("login"), frame.getHeaders().get("passcode")));
        {
            connections.send(connectionId, "CONNECTED");
           // if(containsReceipt(frame))

        }



       /*  if(frame.getHeaders().containsKey("RECEIPT"));
        {
            int receipteId=0;
            try{
                 receipteId = Integer.parseInt(frame.getHeaders().get("RECEIPT"));
                System.out.println(receipteId); // output = 25
            }
            catch (NumberFormatException ex){
                ex.printStackTrace();
            }
            FrameReceipt receiptFrame = new FrameReceipt(receipteId);
            //connections.send(connectionId, (T)receiptFrame); 
        }
        */
    }

    public void executeSubscrice(StompFrame frame)
    {
        if(connections.sub(connectionId, frame.getHeaders().get("destination"), stringToInt(frame.getHeaders().get("id"))))
            connections.send(connectionId, "SUBSCRIBED" + "\n" +"receipt-id:"+frame.getHeaders().get("receipt"));

    }

    public void executeUnsubscribe(StompFrame frame)
    {
        if(connections.unsub(connectionId, stringToInt(frame.getHeaders().get("id")))) 
            connections.send(connectionId, "UNSUBSCRIBED" + "\n" +"receipt-id:"+ frame.getHeaders().get("receipt")); 


    }
    
    public void executeDisconnect(StompFrame frame)
    {
        connections.send(connectionId, "DISCONNECTED\n"+"receipt-id:"+frame.getHeaders().get("receipt")); 
        connections.disconnect(connectionId);
    }
    public void executeSend(StompFrame frame,String msg)
    {
        connections.send(frame.getHeaders().get("destination"), msg);
    }


    public int stringToInt(String str)
    {
        int num;
        try {
            num = Integer.parseInt(str);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input: " + str);
            num = 0;
        }
        return num;
    }
}
/*
try{
            int number = Integer.parseInt(frame.getHeaders().get("RECEIPT"));
            System.out.println(number); // output = 25
        }
        catch (NumberFormatException ex){
            ex.printStackTrace();
        }
 * עשות מחלקה לכל פריים בנפרד בתיקייה סטומפ.
לכתוב פה את הפעולות שמבצעות את כל הדברים בכל פריימ
בפעולה פרוסס יהיה סוויצ׳ קייס על הערך של הקומנד והוא יקרא לכל אחת מהפעולות האלה בהתאם לקומנד שהתקבל.
 * sholud have a strat function
 */
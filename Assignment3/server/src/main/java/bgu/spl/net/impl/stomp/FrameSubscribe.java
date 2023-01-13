package bgu.spl.net.impl.stomp;

import java.util.HashMap;
import java.util.Map;


public class FrameSubscribe 
{
    private String destination = null;
    private String subid = null;    
    private Map<String, String> headers = new HashMap<>();

    public FrameSubscribe(StompFrame frame)
    {
        headers = frame.getHeaders();
        this.destination = headers.get("destination");
        this.subid = headers.get("id");
    }

    //validate!!!
}

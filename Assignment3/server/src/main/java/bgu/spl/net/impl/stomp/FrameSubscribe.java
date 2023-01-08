package bgu.spl.net.impl.stomp;

import java.util.HashMap;
import java.util.Map;


public class FrameSubscribe 
{
    private String destenation = null;
    private String id = null;    
    private Map<String, String> headers = new HashMap<>();

    public FrameSubscribe(StompFrame frame)
    {
        headers = frame.getHeaders();
        this.destenation = headers.get("destenation");
        this.id = headers.get("id");
    }

    //validate!!!
}

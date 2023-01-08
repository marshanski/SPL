package bgu.spl.net.impl.stomp;

import java.util.HashMap;
import java.util.Map;

public class FrameDisconnect 
{
    private String id = null;
    private Map<String, String> headers = new HashMap<>();
    public FrameDisconnect(StompFrame frame)
    {
        headers = frame.getHeaders();
        this.id = headers.get("id");
        
    }    
}

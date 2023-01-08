package bgu.spl.net.impl.stomp;

import java.util.HashMap;
import java.util.Map;

public class FrameSend 
{
    private String destenation = null;
    private String body= null;
    private Map<String, String> headers = new HashMap<>();

    public FrameSend(StompFrame frame)
    {
        headers = frame.getHeaders();
        this.destenation = headers.get("destenation");
        this.body = frame.getBody();
    }

}

package bgu.spl.net.impl.stomp;

import java.util.HashMap;
import java.util.Map;

public class FrameDisconnect 
{
    private String id = null;
    StringBuilder errors = new StringBuilder();
    private String allErrors;
    private Map<String, String> headers = new HashMap<>();
    public FrameDisconnect(StompFrame frame)
    {
        headers = frame.getHeaders();
        this.id = headers.get("id");
        
    } 
    
    public boolean validate()
    {
        boolean valid = false;
        if(this.id == null)
        {
            errors.append("there is an error with the ID you provided" + "\n");
            valid = true;
        }
        if(valid)
            return true;
        else
        {
            allErrors = errors.toString();
            return false;
        }
            

    } 
}

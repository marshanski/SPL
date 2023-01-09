package bgu.spl.net.impl.stomp;

import java.util.HashMap;
import java.util.Map;

public class FrameConnect 
{
    private StompCommand command = null;
    private String login = null;
    private String password= null;
    private String host= null;
    private String accept_version= null;
    private Map<String, String> headers = new HashMap<>();

    public FrameConnect(StompFrame frame)
    {
        this.command = frame.getCommand();
        headers = frame.getHeaders();
        this.login = headers.get("login");
        this.password = headers.get("password");
        this.host = headers.get("host");
        this.accept_version = headers.get("accept_version");
    }
   // validate!!! not complete

    public void validate(String header)
    {
        if(header == null)
        {

        }
            
    }
}

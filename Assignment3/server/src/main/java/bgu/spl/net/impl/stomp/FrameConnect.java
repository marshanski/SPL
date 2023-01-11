package bgu.spl.net.impl.stomp;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class FrameConnect 
{
    private StompCommand command = null;
    private String login = null;
    private String password= null;
    private String host= null;
    private String accept_version= null;
    private Map<String, String> headers = new HashMap<>();
    StringBuilder errors = new StringBuilder();
    private String allErrors; 

    public FrameConnect(StompFrame frame)
    {
        this.command = frame.getCommand();
        headers = frame.getHeaders();
        this.login = headers.get("login");
        this.password = headers.get("password");
        this.host = headers.get("host");
        this.accept_version = headers.get("accept_version");
        if(!validate())
        {  

        }

    }
   // validate!!! not complete

    public boolean validate()
    {
        boolean valid = false;
        if(this.login == null)
        {
            errors.append("there is an error with the ID you provided" + "\n");
            valid = true;
        }
        if(this.password ==  null)
        {
            errors.append("there is an error with the PASSCODE you provided" + "\n");
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

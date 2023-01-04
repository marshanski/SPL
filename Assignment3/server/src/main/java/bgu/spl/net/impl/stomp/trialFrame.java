package bgu.spl.net.impl.stomp;

import java.io.Serializable;

public class trialFrame implements java.io.Serializable
{
    private String message;
    public trialFrame(String message)
    {
        this.message = message;
    }

    private void print()
    {
        System.out.println(this.message);
    }
    
}

package bgu.spl.net.impl.stomp;

public enum StompCommand
{
    CONNECT("CONNECT"),
    CONNECTED("CONNECTED"),
    DISCONNECT("DISCONNECT"),
    ERROR("ERROR"),
    MESSAGE("MESSAGE"),
    RECEIPT("RECEIPT"),
    SEND("SEND"),
    SUBSCRIBE("SUBSCRIBE"),
    UNSUBSCRIBE("UNSUBSCRIBE");

    private final String value;

    public static StompCommand fromValue(String value) {
        for (StompCommand c : StompCommand.values()) {
            if (c.value.equals(value)) {
                return c;
            }
        }
        throw new IllegalArgumentException("Unknown STOMP command: " + value);
    }

    private StompCommand(String value) 
    {
        this.value = value;
    }

    @Override
    public String toString() 
    {
        return this.value;
    }
    public void test()
    {
        for(StompCommand test: StompCommand.values())
    {
        System.out.println(test);
    }
    }
    

}
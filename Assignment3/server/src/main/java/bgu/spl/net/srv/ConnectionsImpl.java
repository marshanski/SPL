package bgu.spl.net.srv;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
public class ConnectionsImpl implements Connections 
{
    //mapping between <ConnectionId , ConnectionHandler>:
    private ConcurrentHashMap<Integer,ConnectionHandler<T>> clients;
    
    //maping all the users that ever connected to the server <username,passcode>:
    private ConcurrentHashMap<String,String> users;

    //mapping all the users that are currently logged in the server <username,connectionId>:
    private ConcurrentHashMap<Integer,String> userToClient;

    //mapping between channels and users that connected to that channel using a map that maps connectionId to SubscribeId 
    //<channelName , <ConnectionId , SubscribeId>>:
    private ConcurrentHashMap<String,ConcurrentHashMap<Integer,Integer>> channels;
    private int connections;

    public ConnectionsImpl()
    {
        this.clients      = new ConcurrentHashMap<Integer,BlockingConnectionHandler<T>>();
        this.users        = new ConcurrentHashMap<String,String>();
        this.userToClient = new ConcurrentHashMap<Integer,String>();
        this.channels     = new ConcurrentHashMap<String,ConcurrentHashMap<Integer,Integer>>();
        this.connections = 0;
    }

    public boolean send(int connectionId, T msg)
    {
        BlockingConnectionHandler<String> bch = clients.get(connectionId);
        bch.send(msg);

    }







    
}


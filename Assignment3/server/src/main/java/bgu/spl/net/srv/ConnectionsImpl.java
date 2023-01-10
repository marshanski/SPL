package bgu.spl.net.srv;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
public class ConnectionsImpl<T> implements Connections<T> 
{
    //mapping between <ConnectionId , ConnectionHandler>:
    private ConcurrentHashMap<Integer,ConnectionHandler<T>> clients;
    
    //maping all the users that ever connected to the server <username,passcode>:
    private ConcurrentHashMap<String,String> users;

    //mapping all the users that are currently logged in the server <username,connectionId>:
    private ConcurrentHashMap<String,Integer> activeUsers;

    //mapping between channels and users that connected to that channel using a map that maps connectionId to SubscribeId 
    //<channelName , <ConnectionId , SubscribeId>>:
    private ConcurrentHashMap<String,ConcurrentHashMap<Integer,Integer>> channelsToUsers;
    private int numOfConnections;

    public ConnectionsImpl()
    {
        this.clients          = new ConcurrentHashMap<Integer,ConnectionHandler<T>>();
        this.users            = new ConcurrentHashMap<String,String>();
        this.activeUsers      = new ConcurrentHashMap<String,Integer>();
        this.channelsToUsers  = new ConcurrentHashMap<String,ConcurrentHashMap<Integer,Integer>>();
        this.numOfConnections = 0;
    }

    public void send(int connectionId, T msg)
    {
        clients.get(connectionId).send(msg);
    }

    public void disconnect(int connectionId)
    {
        for (Map.Entry<String,ConcurrentHashMap<Integer,Integer>> entry : channelsToUsers.entrySet())
        {
            entry.getValue().remove(connectionId); // deleteing the user from all topics
        }
        clients.remove(connectionId); // removing the client's connection handler from the map clients.
        

    }



    
}


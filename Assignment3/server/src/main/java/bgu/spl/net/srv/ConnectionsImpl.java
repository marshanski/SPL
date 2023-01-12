package bgu.spl.net.srv;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class ConnectionsImpl<T> implements Connections<T> 
{
    //mapping between <ConnectionId , ConnectionHandler>:
    public ConcurrentHashMap<Integer,ConnectionHandler<T>> clients;
    
    //maping all the users that ever connected to the server <username,passcode>:
    public ConcurrentHashMap<String,String> users;

    //mapping all the users that are currently logged in the server <username,connectionId>:
    public ConcurrentHashMap<String,Integer> activeUsers;

    //mapping between channels and users that connected to that channel using a map that maps connectionId to SubscribeId 
    //<channelName , <ConnectionId , SubscribeId>>:
    private ConcurrentHashMap<String,ConcurrentHashMap<Integer,Integer>> channelsToUsers;
    private static int numOfConnections;

    public ConnectionsImpl()
    {
        this.clients          = new ConcurrentHashMap<Integer,ConnectionHandler<T>>();
        this.users            = new ConcurrentHashMap<String,String>();
        this.activeUsers      = new ConcurrentHashMap<String,Integer>();
        this.channelsToUsers  = new ConcurrentHashMap<String,ConcurrentHashMap<Integer,Integer>>();
        this.numOfConnections = 0;
    }

    public void send(int connectionId, String msg)
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

    public boolean connect(int connectionId, String username, String passcode)
    {     
        if(users.contains(username))// the username existes in the database
        {
            if(users.get(username)!= passcode)// check if passcode is matching
                return false;
            else
                activeUsers.put(username, connectionId);
                return true;
        }
        else
        {
            return true;
        }
        

        
        
        
    }
    public int addClient(ConnectionHandler<T> handler)
    {
        int id = numOfConnections;
        numOfConnections++;
        clients.put(id, handler);
        return id;
    }
    
    public void send(String a, String b )
    {
        
    }



    
}






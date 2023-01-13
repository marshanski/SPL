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

    public boolean disconnect(int connectionId)
    {
        for (Map.Entry<String,ConcurrentHashMap<Integer,Integer>> entry : channelsToUsers.entrySet())
        {
            entry.getValue().remove(connectionId); // deleteing the user from all topics
        }
        clients.remove(connectionId); // removing the client's connection handler from the map clients.
        return true;
    }

    public String connect(int connectionId, String username, String passcode)
    {     
        if(!isAvailable(username))// the username existes in the database
        {
            if(!isPasscodeRight(username, passcode))// check if passcode is matching
                return "ERROR\nPASSCODE\n";
            return "ERROR\nUSERNAME\n";
        }
        else
        {
            users.put(username, passcode);
            activeUsers.put(username, connectionId);
            return "CONNECTED\n"+username+"\n"+passcode;
        }
    }

    public int addClient(ConnectionHandler<T> handler)
    {
        int id = numOfConnections;
        numOfConnections++;
        clients.put(id, handler);
        return id;
    }
    
    public boolean sub(int connectionId, String channelName, int subscribeId)
    {
        if(!channelsToUsers.isEmpty())
        {
            if(channelsToUsers.containsKey(channelName))
            {
                if(channelsToUsers.get(channelName).containsKey(connectionId))
                    return false;
                channelsToUsers.get(channelName).put(connectionId, subscribeId);
                return true;
            }
        }
        ConcurrentHashMap<Integer,Integer> hash =  new ConcurrentHashMap<Integer,Integer>();
        channelsToUsers.put(channelName,hash);
        channelsToUsers.get(channelName).put(connectionId, subscribeId);
        return true;
    }

    public boolean unsub(int connectionId, int subscribeId)
    {
        if(!channelsToUsers.isEmpty())
        {
            for (Map.Entry<String,ConcurrentHashMap<Integer,Integer>> entry : channelsToUsers.entrySet())
            {
                if(entry.getValue().get(connectionId) == subscribeId)
                {
                    entry.getValue().remove(connectionId,subscribeId);
                    return true;
                }
            }
        }
        return false;
    }

    public void send(String channel, String msg)
    {
        ConcurrentHashMap<Integer,Integer> hash =  channelsToUsers.get(channel);
        for (Map.Entry<Integer,Integer> entry : hash.entrySet())
        {
            send(entry.getKey(), msg);
        }

    }

    public boolean isAvailable(String username)
    {
        if(users.containsKey(username))
            return false;
        return true;
    }

    public boolean isPasscodeRight(String user, String pass)
    {
        if(users.containsKey(user)&& users.get(user) != pass)
            return false;
        return true;
    }

}






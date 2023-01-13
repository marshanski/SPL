package bgu.spl.net.impl.stomp;


import bgu.spl.net.impl.rci.ObjectEncoderDecoder;
import bgu.spl.net.impl.rci.RemoteCommandInvocationProtocol;
import bgu.spl.net.srv.Server;
import bgu.spl.net.impl.newsfeed.NewsFeed;


public class StompServerTPC {

    public static void main(String[] args) 
    {
        NewsFeed feed = new NewsFeed(); 
        Server.threadPerClient(
                7777, //port
                () -> new StompProtocol<String>(), //protocol factory
                () -> new StompMessageEncoderDecoder<String>()  //message encoder decoder factory
        ).serve();


    }
}

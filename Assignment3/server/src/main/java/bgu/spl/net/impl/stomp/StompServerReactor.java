package bgu.spl.net.impl.stomp;

import bgu.spl.net.srv.Server;

public class StompServerReactor 
{

    public static void main(String[] args) {

        Server.reactor
        (
                 Runtime.getRuntime().availableProcessors(),
                 7777, //port
                 () -> new StompProtocol<String>(), 
                 () -> new StompMessageEncoderDecoder<String>()//protocol factory 'when we started it was () -> new StompProtocol<>()' StompMessageEncoderDecoder::new 
                 //message encoder decoder factory
         ).serve();
    }
}

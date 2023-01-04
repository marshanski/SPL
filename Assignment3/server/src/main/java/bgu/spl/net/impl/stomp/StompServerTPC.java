package bgu.spl.net.impl.stomp;

import bgu.spl.net.srv.Server;

public class StompServerTPC {

    public static void main(String[] args) {

        Server.threadPerClient
        (
                7777, //port
                () -> new StompProtocol(), //protocol factory
                StompMessageEncoderDecoder::new //message encoder decoder factory
        ).serve();


    }
}

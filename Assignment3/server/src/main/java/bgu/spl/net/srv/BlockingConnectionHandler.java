package bgu.spl.net.srv;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.ConnectionsImpl;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.net.Socket;
import bgu.spl.net.impl.stomp.*;

public class BlockingConnectionHandler<T> implements Runnable, ConnectionHandler<T> 
{

    private final StompMessagingProtocol<T> protocol;
    private final StompMessageEncoderDecoder<T> encdec;
    private final Socket sock;
    private BufferedInputStream in;
    private BufferedOutputStream out;
    private volatile boolean connected = true;
    ConnectionsImpl<T> connections;
    private int connectionId;

    public BlockingConnectionHandler(Socket sock, StompMessageEncoderDecoder<T> reader, StompMessagingProtocol<T> protocol, ConnectionsImpl<T> connections)
     {
        this.sock         = sock;
        this.encdec       = reader;
        this.protocol     = protocol;
        this.connections  = connections;
        this.connectionId = connections.addClient(this);
        protocol.start(connectionId,connections);
    }
    @Override
    public void run() 
    {
        try (Socket sock = this.sock) { //just for automatic closing
            int read;

            in = new BufferedInputStream(sock.getInputStream());
            out = new BufferedOutputStream(sock.getOutputStream());

            while (!protocol.shouldTerminate() && connected && (read = in.read()) >= 0) {
                String nextMessage = encdec.decodeNextByte((byte) read);
                if (nextMessage != null) {
                    protocol.process(nextMessage);
                    /*if (response != null) {
                        out.write(encdec.encode(response));
                        out.flush();*/
                    }
                }
            }
            catch (IOException ex) {
                ex.printStackTrace();

        } 
    }

    @Override
    public void close() throws IOException {
        connected = false;
        if(connections.userIsActive(connectionId))
            this.connections.disconnect(this.connectionId);
        sock.close();
    }

    @Override
    public void send(String msg) 
    {
        //IMPLEMENT IF NEEDED
        try {
            out.write(encdec.encode(msg));
            out.flush();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}

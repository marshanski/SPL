package bgu.spl.net.srv;

import bgu.spl.net.api.*;
import java.io.IOException;
import java.net.ServerSocket;
import bgu.spl.net.srv.BlockingConnectionHandler;
import java.net.Socket;
import java.util.function.Supplier;
import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.impl.stomp.*;
import java.util.List;
import java.util.ArrayList;

public abstract class BaseServer<T> implements Server<T> {

    private final int port;
    private final Supplier<StompProtocol<T>> protocolFactory;
    private final Supplier<StompMessageEncoderDecoder<T>> encdecFactory;
    private ServerSocket sock;
    private ConnectionsImpl<T> connections;

    public BaseServer(
            int port,
            Supplier<StompProtocol<T>> protocolFactory,
            Supplier<StompMessageEncoderDecoder<T>> encdecFactory) {

        this.port = port;
        this.protocolFactory = protocolFactory;
        this.encdecFactory = encdecFactory;
		this.sock = null;
    }

    @Override
    public void serve() {

        try (ServerSocket serverSock = new ServerSocket(port)) {
			System.out.println("Server started");

            this.sock = serverSock; 
            ConnectionsImpl<T> connections = new ConnectionsImpl<>();//just to be able to close
            List<BlockingConnectionHandler<T>> connectionHandlers = new ArrayList<>();

            while (!Thread.currentThread().isInterrupted()) 
            {
                Socket clientSock                    = serverSock.accept();
                BlockingConnectionHandler<T> handler = new BlockingConnectionHandler(clientSock,this.encdecFactory.get(),protocolFactory.get(),connections);
                connectionHandlers.add(handler);
                execute(handler);
            }
        } catch (IOException ex) {
        }

        System.out.println("server closed!!!");
    }

    @Override
    public void close() throws IOException {
		if (sock != null)
			sock.close();
    }

    protected abstract void execute(BlockingConnectionHandler<T>  handler);

}

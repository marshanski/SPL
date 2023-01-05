package bgu.spl.net.impl.echo;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

import bgu.spl.net.impl.rci.RCIClient;


public class EchoClientRci 
{

    public static void main(String[] args) throws IOException 
    {

        if (args.length == 0) {
            args = new String[]{"localhost", "hello"};
        }

        if (args.length < 2) {
            System.out.println("you must supply two arguments: host, message");
            System.exit(1);
        }

        //BufferedReader and BufferedWriter automatically using UTF-8 encoding
        
        RCIClient client = new RCIClient(args[0], 7777);
        System.out.println("sending message to server");


        System.out.println("awaiting response");

        //System.out.println("message from server: " + line);
        
    }
}

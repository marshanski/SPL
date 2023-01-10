
#include <stdlib.h>
#include "../include/ConnectionHandler.h"
#include <thread>
#include <iostream>



void ReceiveThread(ConnectionHandler& connectionHandler)
{
	while (connectionHandler.isAlive()) 
    {
		int len;

        std::string answer;

        if (!connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        
		len=answer.length();
        answer.resize(len-1);
        //std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") 
		{
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
	}

}


void SendThread(ConnectionHandler& connectionHandler)
{
    while (connectionHandler.isAlive()) 
    {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
		std::string line(buf);
		int len=line.length();
        if (!connectionHandler.sendLine(line))
		{
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
		// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        //std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
	}

	
}

int main (int argc, char *argv[]) 
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    //definding the host and the port
    std::string host = argv[1];
    short port = atoi(argv[2]);
    
    //create the connection, means create a socket to connect with
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
	std::thread send_thread(SendThread, std::ref(connectionHandler));
  	std::thread receive_thread(ReceiveThread, std::ref(connectionHandler));

	send_thread.join();
  	receive_thread.join();

    return 0;
}


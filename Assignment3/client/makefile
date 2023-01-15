CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lpthread

all: StompWCIClient

EchoClient: bin/ConnectionHandler.o bin/echoClient.o bin/Frame.o
	g++ -o bin/EchoClient bin/ConnectionHandler.o bin/echoClient.o bin/Frame.o $(LDFLAGS)

StompWCIClient: bin/ConnectionHandler.o bin/StompWCIClient.o bin/event.o  bin/user.o bin/Frame.o 
	g++ -o bin/StompWCIClient bin/ConnectionHandler.o bin/StompWCIClient.o bin/event.o bin/user.o bin/Frame.o  $(LDFLAGS)

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/echoClient.o: src/echoClient.cpp
	g++ $(CFLAGS) -o bin/echoClient.o src/echoClient.cpp

bin/event.o: src/event.cpp
	g++ $(CFLAGS) -o bin/event.o src/event.cpp

bin/user.o: src/user.cpp
	g++ $(CFLAGS) -o bin/user.o src/user.cpp

bin/Frame.o: src/Frame.cpp
	g++ $(CFLAGS) -o bin/Frame.o src/Frame.cpp

bin/StompWCIClient.o: src/StompWCIClient.cpp
	g++ $(CFLAGS) -o bin/StompWCIClient.o src/StompWCIClient.cpp

.PHONY: clean
clean:
	rm -f bin/*
	
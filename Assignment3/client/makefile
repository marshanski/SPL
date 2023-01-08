CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lpthread

all: StompClient

EchoClient: bin/ConnectionHandler.o bin/echoClient.o bin/Connect.o
	g++ -o bin/EchoClient bin/ConnectionHandler.o bin/echoClient.o bin/Connect.o $(LDFLAGS)

StompClient: bin/ConnectionHandler.o bin/StompClient.o bin/event.o bin/Connect.o bin/user.o
	g++ -o bin/StompClient bin/ConnectionHandler.o bin/StompClient.o bin/event.o  bin/Connect.o bin/user.o $(LDFLAGS)

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/echoClient.o: src/echoClient.cpp
	g++ $(CFLAGS) -o bin/echoClient.o src/echoClient.cpp

bin/event.o: src/event.cpp
	g++ $(CFLAGS) -o bin/event.o src/event.cpp

bin/user.o: src/user.cpp
	g++ $(CFLAGS) -o bin/user.o src/user.cpp

bin/Connect.o: src/Connect.cpp
	g++ $(CFLAGS) -o bin/Connect.o src/Connect.cpp

bin/StompClient.o: src/StompClient.cpp
	g++ $(CFLAGS) -o bin/StompClient.o src/StompClient.cpp

.PHONY: clean
clean:
	rm -f bin/*
	

all: clean compile link

link:
	g++ -o bin/main bin/main.o bin/Agent.o  bin/Graph.o bin/Parser.o bin/Party.o   bin/Simulation.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/main.o       src/main.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Agent.o      src/Agent.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Graph.o      src/Graph.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Parser.o     src/Parser.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Party.o      src/Party.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Simulation.o src/Simulation.cpp
	
clean:
	rm -f bin/*
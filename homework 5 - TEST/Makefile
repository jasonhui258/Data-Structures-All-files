netdriver.out: Node.o maxfinder.o NetDriver.o 
	g++ -Wall -ansi -g -o netdriver.out Node.o maxfinder.o NetDriver.o 

maxfinder.o: maxfinder.cpp NetDriver.h maxfinder.h QuadraticProbing.h QueueLL.h LinkedList.h
	g++ -Wall -ansi -g -c maxfinder.cpp

NetDriver.o: NetDriver.cpp CPUTimer.h NetDriver.h maxfinder.h 
	g++ -Wall -ansi -g -c NetDriver.cpp

Node.o: Node.cpp Node.h QuadraticProbing.h LinkedList.h 
	g++ -Wall -ansi -g -c Node.cpp


clean:
	rm -f netdriver.out maxfinder.o Node.o NetDriver.o

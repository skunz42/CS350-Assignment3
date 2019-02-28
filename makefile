all:    everything

everything: algorithm.o generator.o driver.o
	g++ -O0 -g -Wall -std=c++11 algorithm.o generator.o driver.o -o pageRep

driver.o:   driver.cpp
	g++ -O0 -g -Wall -std=c++11 -c driver.cpp

algorithm.o:   algorithm.cpp
	g++ -O0 -g -Wall -std=c++11 -c algorithm.cpp

generator.o:   generator.cpp
	g++ -O0 -g -Wall -std=c++11 -c generator.cpp

clean:
	rm -f *.o pageRep

test:   pageRep
	./pageRep

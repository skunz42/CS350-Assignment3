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
	gnuplot -e "title='No-Loccality'" -e "input_filename='no_locality_data.csv'" plot_hit_rates.plt > no_locality.png
	gnuplot -e "title='80-20'" -e "input_filename='eighty_twenty_data.csv'" plot_hit_rates.plt > 80-20.png
	gnuplot -e "title='Looping'" -e "input_filename='looping_data.csv'" plot_hit_rates.plt > looping_plot.png

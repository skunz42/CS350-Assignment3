#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <fstream>
#include "string.h"

#include "generator.h"

class algorithm {
	public:
		static const int TRACE_LEN = 10000;
		algorithm();
		algorithm(generator *);
		~algorithm();
		int fifo(int, int);
		int random(int, int);
		int lru(int, int);
		int optimal(int, int);
		int clock(int, int);
		void writeCSV(int *[3], int *[3], int *[3], int *[3], int *[3]);
	private:
		int nolocality[TRACE_LEN];
		int eightytwenty[TRACE_LEN];
		int looping[TRACE_LEN];
};

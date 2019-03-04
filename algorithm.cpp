#include "algorithm.h"

using namespace std;

algorithm::algorithm() {

}

algorithm::~algorithm() {

}

algorithm::algorithm(generator *g) {
	for (int i = 0; i < algorithm::TRACE_LEN; i++) {
		nolocality[i] = g->getNoLoc(i);
	}
	for (int i = 0; i < algorithm::TRACE_LEN; i++) {
		eightytwenty[i] = g->getEighty20(i);
	}
	for (int i = 0; i < algorithm::TRACE_LEN; i++) {
		looping[i] = g->getLoop(i);
	}
}

int algorithm::fifo(int tableSize, int workload) {
	int workArr[algorithm::TRACE_LEN];
	int hitCount = 0;
	int tableIndex = 0;
	int table[tableSize] = {-1}; //set all values to -1 so we know which spots are empty
	bool inTable; //check if value from trace is in the page table

	//workload parameter chooses which array to use. copy contents of the
	//selected array to a working array so we don't repeat code
	if (workload == 0) { //No locality
		copy(begin(nolocality), end(nolocality), begin(workArr));
	} else if (workload == 1) { //eighty twenty
		copy(begin(eightytwenty), end(eightytwenty), begin(workArr));
	} else { //looping
		copy(begin(looping), end(looping), begin(workArr));
	}
	//Calculate number of hits
	for (int i = 0; i < algorithm::TRACE_LEN; i++) {
		int pageNum = workArr[i];
		inTable = false;
		for (int j = 0; j < tableSize; j++) {
			if (table[j] == pageNum) { //page number is in table
				inTable = true;
				hitCount++;
				break;
			}
		}
		if (!inTable) { //evict oldest page number
			table[tableIndex%tableSize] = pageNum;
			tableIndex++;
		}
	}
	return hitCount;
}

int algorithm::random(int tableSize, int workload) {
	int workArr[algorithm::TRACE_LEN];
	int hitCount = 0;
	int tableIndex = 0;
	int table[tableSize] = {-1}; //set all values to -1 so we know which spots are empty
	bool inTable; //check if value from trace is in the page table

	//workload parameter chooses which array to use. copy contents of the
	//selected array to a working array so we don't repeat code
	if (workload == 0) { //No locality
		copy(begin(nolocality), end(nolocality), begin(workArr));
	} else if (workload == 1) { //eighty twenty
		copy(begin(eightytwenty), end(eightytwenty), begin(workArr));
	} else { //looping
		copy(begin(looping), end(looping), begin(workArr));
	}
	for (int i = 0; i < algorithm::TRACE_LEN; i++) {
		int pageNum = workArr[i];
		inTable = false;
		for (int j = 0; j < tableSize; j++) {
			if (table[j] == pageNum) { //page number is in table
				inTable = true;
				hitCount++;
				break;
			}
		}
		if (!inTable) { //evict random page number
			tableIndex = rand()%tableSize;
			table[tableIndex] = pageNum;
		}
	}
	return hitCount;
}

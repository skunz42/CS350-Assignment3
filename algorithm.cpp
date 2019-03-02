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
	int table[tableSize];
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
}

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

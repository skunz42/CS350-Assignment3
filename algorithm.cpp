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

int algorithm::lru(int tableSize, int workload) {
	int workArr[algorithm::TRACE_LEN];
	int hitCount = 0;
	//int tablieIndex = 0;
	int table[tableSize] = {-1}; //set all values to -1 so we know which spots are empty
	int lruTable[tableSize] = {-1}; //table for timestamps of pages in page table
	int lru; //value of lru page
	int lruIndex; //index in pt of lru value
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
		lru = INT_MAX;
		for (int j = 0; j < tableSize; j++) {
			if (table[j] == pageNum) { //page number is in table
				inTable = true;
				lruTable[j] = i; //update timestamp
				hitCount++;
				break;
			}
		}
		if (!inTable) { //evict lru page number
			//tableIndex = rand()%tableSize;
			for (int j = 0; j < tableSize; j++) {
				if (lruTable[j] < lru) { //older timestamp
					lru = lruTable[j];
					lruIndex = j;
				}
			}
			table[lruIndex] = pageNum;
			lruTable[lruIndex] = i;
		}
	}
	return hitCount;
}

int algorithm::optimal(int tableSize, int workload){
	int workArr[algorithm::TRACE_LEN];
	int hitCount = 0;
	//int tableIndex = 0;
	int table[tableSize] = {-1}; 
	bool inTable;
	bool placed;
	int furthestOut[tableSize] = {-1};
	int furthestIdx;
	int tmp;

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
		if (!inTable) { 
			placed = false;			
			for (int k = 0; k < tableSize; k++){ // first look for empty table
				if (table[k] == -1){			// entries to account for 
					placed = true;				// compulsory misses
					table[k] = pageNum;	
					break;
				}							
			}
			if(!placed){ // if the page has not been placed, the cache is full:
				int m;			// evict page used furthest in the future
				for (m = 0; m < tableSize; m++){
					furthestOut[m] = -1; // if you dont understand this reset to 
				} 							// -1 just ask and i'll explain
				for (m = 0; m < tableSize; m++){
					for(furthestIdx = (i+1); furthestIdx < algorithm::TRACE_LEN; 
					furthestIdx++){ // starting at the next idx in the trace
						if(table[m] == workArr[furthestIdx]){ // track the first
							furthestOut[m] = furthestIdx; // occurence of each
							break; // page that is currently in the table
						}			
					}			
				}					
				furthestIdx = -1;
				tmp = -1;
				for(m = 0; m < tableSize; m++){ // then place the new page at the 
					if(furthestOut[m] > tmp){ // table idx associated with the 
						tmp = furthestOut[m]; // largest next occurence idx
						furthestIdx = m;
					}
				}
				table[furthestIdx] = pageNum;
			}
		}
	}
	return hitCount;
}
			

int algorithm::clock(int tableSize, int workload){
	int workArr[algorithm::TRACE_LEN];
	int hitCount = 0;
	//int tableIndex = 0;
	int table[tableSize] = {-1};
	bool inTable; 
	bool placed;
	int clockHand = 0;
	int useBit[tableSize] = {-1};

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
				useBit[j] = 1;
				break;
			}
		}
		if (!inTable) { 
			placed = false;			
			for (int k = 0; k < tableSize; k++){ // first look for empty table
				if (table[k] == -1){			// entries to account for 
					placed = true;				// compulsory misses
					table[k] = pageNum;	
					useBit[k] = 1;
					break;
				}							
			}
			while(!placed){  // cache is full cycle through and evict appropriately 
				if(useBit[clockHand] == 0){
					table[clockHand] = pageNum;
					useBit[clockHand] = 1;
					placed = true;
				}
				else{
					useBit[clockHand] = 0;						
					clockHand = (clockHand+1) % tableSize;
				}
			}
		}
	}
	return hitCount;
}



















								


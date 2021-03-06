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
	int table[tableSize]; //set all values to -1 so we know which spots are empty
	memset(table, -1, tableSize*sizeof(table[0]));
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
	int table[tableSize]; //set all values to -1 so we know which spots are empty
	memset(table, -1, tableSize*sizeof(table[0]));
	bool inTable; //check if value from trace is in the page table
	bool isFull;

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
		isFull = true;
		for (int j = 0; j < tableSize; j++) {
			if (table[j] == pageNum) { //page number is in table
				inTable = true;
				hitCount++;
				break;
			}
		}
		if (!inTable) { //evict random page number
			for (int j = 0; j < tableSize; j++) {
				if (table[j] == -1) {
					table[j] = pageNum;
					isFull = false;
					break;
				}
			}
			if (isFull) {
				tableIndex = rand()%tableSize;
				table[tableIndex] = pageNum;
			}
		}
	}
	return hitCount;
}

int algorithm::lru(int tableSize, int workload) {
	int workArr[algorithm::TRACE_LEN];
	int hitCount = 0;
	//int tablieIndex = 0;
	int table[tableSize]; //set all values to -1 so we know which spots are empty
	int lruTable[tableSize]; //table for timestamps of pages in page table
	memset(table, -1, tableSize*sizeof(table[0]));
	memset(lruTable, -1, tableSize*sizeof(table[0]));
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
	int table[tableSize]; // = {-1}; 
	bool inTable;
	bool placed;
	int furthestOut[tableSize]; // = {algorithm::TRACE_LEN};
	int furthestIdx;
	int tmp;

	for(int i = 0; i < tableSize; i++){
		table[i] = -1;
		furthestOut[i] = algorithm::TRACE_LEN;
	}
	
	if (workload == 0) { //No locality
		copy(begin(nolocality), end(nolocality), begin(workArr));
	} else if (workload == 1) { //eighty twenty
		copy(begin(eightytwenty), end(eightytwenty), begin(workArr));
	} else { //looping
		copy(begin(looping), end(looping), begin(workArr));
	}

	for (int i = 0; i < algorithm::TRACE_LEN; i++) {
		int pageNum = workArr[i];
		//cout << pageNum << endl;
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
					furthestOut[m] = (algorithm::TRACE_LEN); // if you dont understand this reset to 
				} 							// traceLen just ask and i'll explain
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
	//cout << tableSize << "\t" << hitCount << endl;
	return hitCount;
}
			

int algorithm::clock(int tableSize, int workload){
	int workArr[algorithm::TRACE_LEN];
	int hitCount = 0;
	//int tableIndex = 0;
	int table[tableSize]; // = {-1};
	bool inTable; 
	bool placed;
	int clockHand = 0;
	int useBit[tableSize]; //= {-1};

	for(int i = 0; i < tableSize; i++){
		table[i] = -1;
		useBit[i] = -1;;
	}

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

void algorithm::writeCSV(int **optArr, int **lruArr, int **fifoArr, int **randArr, int **clockArr) {
	int workloadSize = 20;
	ofstream myfile;
	ofstream myfile2;
	ofstream myfile3;

	//No-Locality
	myfile.open("no_locality_data.csv");
	myfile << "#cache, OPT, LRU, FIFO, RAND, CLOCK\n";
	myfile << "0, 0, 0, 0, 0, 0\n";
	for (int i = 0; i < workloadSize; i++) {
		myfile << 5*(i+1) << "," << 100.0*(optArr[0][i])/algorithm::TRACE_LEN << "," << 100.0*lruArr[0][i]/algorithm::TRACE_LEN << "," << 100.0*fifoArr[0][i]/algorithm::TRACE_LEN << "," << 100.0*randArr[0][i]/algorithm::TRACE_LEN << "," << 100.0*clockArr[0][i]/algorithm::TRACE_LEN << "\n";
	}
	myfile.close();

	//80-20
	myfile2.open("eighty_twenty_data.csv");
	myfile2 << "#cache, OPT, LRU, FIFO, RAND, CLOCK\n";
	myfile2 << "0, 0, 0, 0, 0, 0\n";
	for (int i = 0; i < workloadSize; i++) {
		myfile2 << 5*(i+1) << "," << 100.0*(optArr[1][i])/algorithm::TRACE_LEN << "," << 100.0*lruArr[1][i]/algorithm::TRACE_LEN << "," << 100.0*fifoArr[1][i]/algorithm::TRACE_LEN << "," << 100.0*randArr[1][i]/algorithm::TRACE_LEN << "," << 100.0*clockArr[1][i]/algorithm::TRACE_LEN << "\n";
	}
	myfile2.close();

	//Looping
	myfile3.open("looping_data.csv");
	myfile3 << "#cache, OPT, LRU, FIFO, RAND, CLOCK\n";
	myfile3 << "0, 0, 0, 0, 0, 0\n";
	for (int i = 0; i < workloadSize; i++) {
		myfile3 << 5*(i+1) << "," << 100.0*(optArr[2][i])/algorithm::TRACE_LEN << "," << 100.0*lruArr[2][i]/algorithm::TRACE_LEN << "," << 100.0*fifoArr[2][i]/algorithm::TRACE_LEN << "," << 100.0*randArr[2][i]/algorithm::TRACE_LEN << "," << 100.0*clockArr[2][i]/algorithm::TRACE_LEN << "\n";
	}
	myfile3.close();
}



















								


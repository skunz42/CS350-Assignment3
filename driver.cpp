//#include "driver.h"
#include "algorithm.h"

int main(int argc, char **argv){
	generator *gen = new generator();
	algorithm *algo = new algorithm(gen);

	int workloadSize = 20;
	int workloads[workloadSize];
	int fifoNoLoc[workloadSize];
	int fifoEightyTwenty[workloadSize];
	int fifoLooping[workloadSize];
	int randNoLoc[workloadSize];
	int randEightyTwenty[workloadSize];
	int randLooping[workloadSize];
	int optNoLoc[workloadSize];
	int optEightyTwenty[workloadSize];
	int optLooping[workloadSize];
	int clockNoLoc[workloadSize];
	int clockEightyTwenty[workloadSize];
	int clockLooping[workloadSize];
	int lruNoLoc[workloadSize];
	int lruEightyTwenty[workloadSize];
	int lruLooping[workloadSize];

	int *fifoArr[3] = {fifoNoLoc, fifoEightyTwenty, fifoLooping};
	int *randArr[3] = {randNoLoc, randEightyTwenty, randLooping};
	int *optArr[3] = {optNoLoc, optEightyTwenty, optLooping};
	int *clockArr[3] = {clockNoLoc, clockEightyTwenty, clockLooping};
	int *lruArr[3] = {lruNoLoc, lruEightyTwenty, lruLooping};
	
	//Set up workload array for table sizes
	for (int i = 0; i < workloadSize; i++) {
		workloads[i] = 5*(i+1);
	}

	//Loop through workloads
	for (int i = 0; i < workloadSize; i++) {
		fifoNoLoc[i] = algo->fifo(workloads[i], 0);
		fifoEightyTwenty[i] = algo->fifo(workloads[i], 1);
		fifoLooping[i] = algo->fifo(workloads[i], 2);

		randNoLoc[i] = algo->random(workloads[i], 0);
		randEightyTwenty[i] = algo->random(workloads[i], 1);
		randLooping[i] = algo->random(workloads[i], 2);
		
		optNoLoc[i] = algo->optimal(workloads[i], 0);
		optEightyTwenty[i] = algo->optimal(workloads[i], 1);
		optLooping[i] = algo->optimal(workloads[i], 2);
	
		clockNoLoc[i] = algo->clock(workloads[i], 0);
		clockEightyTwenty[i] = algo->clock(workloads[i], 1);
		clockLooping[i] = algo->clock(workloads[i], 2);

		lruNoLoc[i] = algo->lru(workloads[i], 0);
		lruEightyTwenty[i] = algo->lru(workloads[i], 1);
		lruLooping[i] = algo->lru(workloads[i], 2);
	}

	algo->writeCSV(optArr, lruArr, fifoArr, randArr, clockArr);

	delete(gen);
	delete(algo);
    	return 0;
}

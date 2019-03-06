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

	//Testing - print out fifo workloads
	cout << "FIFO No-Locality" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << fifoNoLoc[i] << " ";
	}
	cout << endl;
	cout << "FIFO 80-20" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << fifoEightyTwenty[i] << " ";
	}
	cout << endl;
	cout << "FIFO Looping" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << fifoLooping[i] << " ";
	}
	cout << endl;

	//Testing - print out random workloads
	cout << "RANDOM No-Locality" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << randNoLoc[i] << " ";
	}
	cout << endl;
	cout << "RANDOM 80-20" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << randEightyTwenty[i] << " ";
	}
	cout << endl;
	cout << "RANDOM Looping" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << randLooping[i] << " ";
	}
	cout << endl;

	//Testing - print out optimal workloads
	cout << "OPTIMAL No-Locality" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << optNoLoc[i] << " ";
	}
	cout << endl;
	cout << "OPTIMAL 80-20" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << optEightyTwenty[i] << " ";
	}
	cout << endl;
	cout << "OPTIMAL Looping" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << optLooping[i] << " ";
	}
	cout << endl;

	//Testing - print out clock workloads
	cout << "CLOCK No-Locality" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << clockNoLoc[i] << " ";
	}
	cout << endl;
	cout << "CLOCK 80-20" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << clockEightyTwenty[i] << " ";
	}
	cout << endl;
	cout << "CLOCK Looping" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << clockLooping[i] << " ";
	}
	cout << endl;

	//Testing - print out lru workloads
	cout << "LRU No-Locality" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << lruNoLoc[i] << " ";
	}
	cout << endl;
	cout << "LRU 80-20" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << lruEightyTwenty[i] << " ";
	}
	cout << endl;
	cout << "LRU Looping" << endl;
	for (int i = 0; i < workloadSize; i++) {
		cout << lruLooping[i] << " ";
	}
	cout << endl;
	delete(gen);
	delete(algo);
    	return 0;
}

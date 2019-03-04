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

	// cout the generated traces------------------------------------------------
/*	
	for(int i = 0; i < 55; i++){
		//cout << gen.getNoLoc(i) << endl;
		//cout << gen.getEighty20(i) << endl;
		//cout << gen.getLoop(i) << endl;
	}
*/   
	// end cout ----------------------------------------------------------------
	// test to see if 80/20 is statistically correct ---------------------------
/*    
	int val;
	int hotCount = 0;
	int coldCount = 0;
	for(int i = 0; i < generator::TRACE_LEN; i++){
		val = gen.getEighty20(i);
		if(val < 20){
			hotCount++;
		}
		else{
			coldCount++;
		}
	}
	// if hotCount is roughly 2000
	// and coldCount is roughly 8000 then 
	// 80/20 trace is generated correctly
	cout << hotCount << endl;
	cout << coldCount << endl;
*/
	// end test-----------------------------------------------------------------
	
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
	delete(gen);
	delete(algo);
    	return 0;
}

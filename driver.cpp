#include "driver.h"

int main(int argc, char **argv){
	generator gen = generator();
	
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
    return 0;

}

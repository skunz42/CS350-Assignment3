#include <vector>
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

class generator {
	public:
		static const int TRACE_LEN = 10000;	
		// everything is handled by the constructor
		generator();
		~generator();
		// accessors to be all proper and stuff
		int getNoLoc(int);
		int getEighty20(int);
		int getLoop(int);
	private:
		// workload types --
		// can be static arrays because they are all
		// invariably of len 10,000
		int noLocality[TRACE_LEN];
		int eighty20[TRACE_LEN];
		int looping[TRACE_LEN];
	
		// private methods used by the constructor
		// to populate the workload types
		void makeNoLoc();
		void makeEighty20();
		void makeLoop();
};

#include "generator.h"

generator::generator(){
	srand(time(0));
	this->makeNoLoc();
	this->makeEighty20();
	this->makeLoop();
}

generator::~generator(){

}

int generator::getNoLoc(int idx){
	return this->noLocality[idx];
}

int generator::getEighty20(int idx){
	return this->eighty20[idx];
}

int generator::getLoop(int idx){
	return this->looping[idx];
}

void generator::makeNoLoc(){
	int randomNum;
	for(int i = 0; i < generator::TRACE_LEN; i++){
		randomNum = rand() % 100;
		this->noLocality[i] = randomNum;
	}
}

void generator::makeEighty20(){
	int indicator;
	int randomNum;
	for(int i = 0; i < generator::TRACE_LEN; i++){
		indicator = rand() % 100;
		if(indicator < 20){
			randomNum = (rand() % (99 - 20 + 1)) + 20;
		}
		else{
			randomNum = rand() % 20;
		}
		this->eighty20[i] = randomNum;
	}

}

void generator::makeLoop(){
	int counter = 0;	
	for(int i = 0; i < generator::TRACE_LEN; i++){
		if(counter == 50) counter = 0;		
		this->looping[i] = counter;
		counter++;
	}
}



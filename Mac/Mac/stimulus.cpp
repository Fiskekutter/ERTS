#include "Stimulus.h"



void STIMULUS::generate(void) {
	wait();
	a = 3;
	b = 2;
	wait();
	a = 5;
	b = 7;
	wait();
	a = 6;
	b = 10;
	wait();
	sc_stop();
}
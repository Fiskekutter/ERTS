#pragma once
#include <systemc.h>



SC_MODULE(MONITOR) {
	sc_in<int> c;
	sc_clock clk;

	SC_CTOR(MONITOR) {
		SC_METHOD(simulate);
		sensitive << c;
		dont_initialize();
	}

	void simulate(void);
};

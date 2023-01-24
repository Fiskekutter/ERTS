#pragma once
#include <systemc.h>



SC_MODULE(STIMULUS) {
	sc_in<bool> clk;
	sc_out<int> a;
	sc_out<int> b;

	SC_CTOR(STIMULUS) {
		SC_THREAD(generate);
		sensitive << clk.pos();
		dont_initialize();
	}

	void generate(void);
};
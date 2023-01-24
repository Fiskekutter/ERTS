#pragma once
#include <systemc.h>



SC_MODULE(MAC) {
	sc_in<int> a;
	sc_in<int> b;
	sc_out<int> c;


	SC_CTOR(MAC) {
		SC_METHOD(compute);
		sensitive << a << b;
	}

	void compute(void);
};
#pragma once


#include <systemc.h>
#include <iostream>

SC_MODULE(ModuleSingle) {
	sc_event myEvent;
	sc_uint<4> counter;
	
	SC_CTOR(ModuleSingle) {
		counter = 0;
		SC_THREAD(myMethod);
		SC_METHOD(myMethod2);
		sensitive << myEvent;

		dont_initialize();
	}

	void myMethod(void);
	void myMethod2(void);
};


#pragma once

#include "systemc.h"
#define NUM_BITS 4

SC_MODULE(stim) {
	
	sc_in<bool> stimClk;
	sc_out<bool> stimReset;
	sc_out<sc_uint<NUM_BITS> > stimCtrl;
	sc_out<sc_uint<NUM_BITS> > outSwitch;
	sc_in<sc_uint<NUM_BITS> > inLeds;

	int i;

	SC_CTOR(stim) : stimClk("stimClock"), 
		stimReset("stimReset"), 
		stimCtrl("stimCtrl"), 
		outSwitch("stimSwitch"), 
		inLeds("stimLeds") {
		i = 0;
		SC_THREAD(yep);
		sensitive << stimClk.pos();

		dont_initialize();
	}

	void yep(void) {
		stimReset.write(1);
		wait();
		stimReset.write(0);
		stimCtrl.write(0);
		outSwitch.write(0);
		std::cout << "Writing ctrl: 0" << std::endl;
		while (i < 3)
		{
			std::cout << "Led value: " << inLeds.read() << std::endl;
			i = inLeds.read();
			wait(10, SC_NS);
		}
		wait();
		i = 1;
		wait(10, SC_NS);
		while(i < 9)
		{
			std::cout << "Writing on switches/ctrl: " << i << std::endl;
			stimCtrl.write(i);
			outSwitch.write(i);
			wait(20, SC_NS);
			std::cout << "Led value: " << inLeds.read() << std::endl;
			i++;
		}


		wait();
	}

	
};

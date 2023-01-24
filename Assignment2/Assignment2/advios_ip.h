#pragma once


#include "systemc.h"
#include <iostream>


#define NUM_BITS 4

SC_MODULE(advios) {
	sc_in<bool> clk;
	sc_in<bool> reset;
	sc_in<sc_uint<NUM_BITS> > ctrl;
	sc_in<sc_uint<NUM_BITS> > inSwitch;
	sc_out<sc_uint<NUM_BITS> > outLeds;

	sc_uint<NUM_BITS> control;
	sc_uint<NUM_BITS> ledValue;
	sc_signal<bool> second;
	sc_uint<28> counter;
	sc_uint<NUM_BITS> switches;

	SC_CTOR(advios) : clk("adClk"), 
		reset("adReset"), 
		ctrl("adCtrl"), 
		inSwitch("adSwitch"), 
		outLeds("adLeds") {
		
		counter = 0;
		second = false;
		ledValue = 0;

		SC_CTHREAD(secondsCounter, clk.pos());
		reset_signal_is(reset, true);

		SC_CTHREAD(master, clk.pos());
		reset_signal_is(reset, true);
	}

	void secondsCounter(void);
	void master(void);
};

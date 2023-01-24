#pragma once

#include <systemc.h>
#include "configuration.h"


SC_MODULE(Stimuli){
	// Clock and reset  
	//sc_in_clk clock;		// Clock  
	sc_out<bool> reset;  // Reset   

	// Handshake ports for ST bus  
	//sc_in<bool> ready;  // Ready signal
	//sc_out<bool> valid; // Valid signal   

	// Channel, error and data ports ST bus  
	//sc_out<sc_int<CHANNEL_BITS> > channel;
	//sc_out<sc_int<ERROR_BITS> > error;
	//sc_out<sc_int<DATA_BITS> > data;

	SC_CTOR(Stimuli) {
		SC_THREAD(stimmy);
	}

	void stimmy(void) {
		reset.write(true);

		wait(10, SC_NS);

		reset.write(false);
	}

};
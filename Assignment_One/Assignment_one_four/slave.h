#pragma once

#include <systemc.h>
#include "configuration.h"
#include <fstream>
#include <string>


SC_MODULE(Slave) {
	// Clock and reset  
	sc_in_clk clock;		// Clock  
	sc_in<bool> reset;  // Reset   

	// Handshake ports for ST bus  
	sc_out<bool> ready;  // Ready signal  
	sc_in<bool> valid; // Valid signal   

	// Channel, error and data ports ST bus  
	sc_port<sc_signal_in_if<sc_int<CHANNEL_BITS>>, 0> channel;
	sc_in<sc_int<ERROR_BITS> > error;
	sc_in<sc_int<DATA_BITS> > data;

	SC_CTOR(Slave) {
		SC_THREAD(receiveData);
		sensitive << clock;
		dont_initialize();

		SC_METHOD(storeToText);
	}

	void receiveData(void);
	void storeToText(void);
};
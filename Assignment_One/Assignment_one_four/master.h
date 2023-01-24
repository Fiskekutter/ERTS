#pragma once

#include <systemc.h>
#include "configuration.h"

SC_MODULE(Master) {
	// Clock and reset  
	sc_in_clk clock;		// Clock  
	sc_in<bool> reset;  // Reset   

	// Handshake ports for ST bus  
	sc_in<bool> ready;  // Ready signal
	sc_out<bool> valid; // Valid signal   

	// Channel, error and data ports ST bus  
	sc_port<sc_signal_out_if<sc_int<CHANNEL_BITS>>, 0> channel;
	sc_out<sc_int<ERROR_BITS> > error;
	sc_out<sc_int<DATA_BITS> > data;

	SC_CTOR(Master) {
		SC_THREAD(sendData);
		sensitive << clock;
		dont_initialize();
	}

	void sendData(void);
};
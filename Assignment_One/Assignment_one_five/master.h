#pragma once

#include <systemc.h>
#include "inAdapter.h"
#include "configuration.h"


SC_MODULE(Master) {
	sc_port<sc_fifo_out_if<sc_int<DATA_BITS>>, 0> out;

	SC_CTOR(Master) {
		SC_THREAD(produce);
		dont_initialize();
	}

	void produce(void) {
		while (1) {
			wait(100, SC_NS);
			out[0]->write(0);
		}
	}
};
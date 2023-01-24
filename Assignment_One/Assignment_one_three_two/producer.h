#pragma once

#include "systemc.h"
#include "tcp.h"


SC_MODULE(Producer) {
	sc_port<sc_fifo_out_if<TCPHeader>, 0> out;

	SC_CTOR(Producer) {
		SC_THREAD(produce);

	}

	void produce(void);
};
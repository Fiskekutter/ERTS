#pragma once

#include <systemc.h>
#include "tcp.h"

SC_MODULE(consumer) {
	sc_fifo_in<TCPHeader> chCon;

	SC_CTOR(consumer) {
		SC_THREAD(receive);
		
	}

	void receive(void);
};
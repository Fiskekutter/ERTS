#pragma once
#include <systemc.h>
#include "tcp.h"


SC_MODULE(Consumer) {
	sc_fifo_in<TCPHeader> chCon;

	SC_CTOR(Consumer) {
		SC_THREAD(consume);
	}

	void consume(void);
};
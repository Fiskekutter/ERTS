#include <iostream>
#include <systemc.h>
#include "consumer.h"
#include "producer.h"
#include "tcp.h"

int sc_main(int argc, char	*argv[])
{
	sc_fifo<TCPHeader> ch("ch");
	
	producer Producer("Producer");
	consumer Consumer("Consumer");

	Producer.out(ch);
	Consumer.chCon(ch);

	sc_start(200, SC_MS);

	return 0;
}
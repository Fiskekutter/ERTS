// Assignment_one_three_two.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <systemc.h>
#include "tcp.h"
#include "consumer.h"
#include "producer.h"

int sc_main(int argc, char	*argv[])
{
	sc_fifo<TCPHeader> ch1("ch1");
	sc_fifo<TCPHeader> ch2("ch2");

	Producer producer("Producer");
	Consumer consumer1("Consumer1");
	Consumer consumer2("Consumer2");

	producer.out(ch1);
	producer.out(ch2);

	consumer1.chCon(ch1);
	consumer2.chCon(ch2);
	
	sc_start(200, SC_MS);

	return 0;
}
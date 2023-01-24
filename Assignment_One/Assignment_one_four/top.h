#pragma once
#include <systemc.h>
#include "configuration.h"
#include "slave.h"
#include "master.h"
#include "stimuli.h"

SC_MODULE(TOP) {
	sc_clock myClock;

	sc_signal<bool> valCh;
	sc_signal<bool> rdyCh;
	sc_signal<bool> resCh;
	sc_signal<sc_int<CHANNEL_BITS>> bitCh[2];
	sc_signal<sc_int<ERROR_BITS>> errCh;
	sc_signal<sc_int<DATA_BITS>> dataCh;

	sc_trace_file *tracefile;

	Slave slave;
	Master master;
	Stimuli stim;

	SC_CTOR(TOP) :myClock("myClock"), slave("slave"), master("master"), stim("stim")
	{
		sc_clock("clock", sc_time(CLK_PERIODE, SC_NS));
		
		master.clock(myClock);
		slave.clock(myClock);
		
		master.valid(valCh);
		master.ready(rdyCh);

		slave.valid(valCh);
		slave.ready(rdyCh);

		for (int i = 0; i < 2; i++) 
		{
			master.channel(bitCh[i]);
			slave.channel(bitCh[i]);
		}
		

		master.error(errCh);
		slave.error(errCh);

		master.data(dataCh);
		slave.data(dataCh);

		stim.reset(resCh);
		master.reset(resCh);
		slave.reset(resCh);

		start_of_simulation();
	}

	~TOP() {
		end_of_simulation();
	}

	void start_of_simulation() {
		tracefile = sc_create_vcd_trace_file("Tracefile");
		//tracefile->set_time_unit(1, SC_NS);

		sc_trace(tracefile, valCh, "Valid");
		sc_trace(tracefile, rdyCh, "Ready");
		sc_trace(tracefile, resCh, "Reset");
		for (int i = 0; i < 2; i++) {
			sc_trace(tracefile, bitCh[i], "Channel_bits" + (char) i);
		}
		sc_trace(tracefile, errCh, "Error_bits");
		sc_trace(tracefile, dataCh, "Data_bits");
		sc_trace(tracefile, myClock, "Clk");
	}

	void end_of_simulation() {
		std::cout << "closing tracefile" << std::endl;
		sc_close_vcd_trace_file(tracefile);
	}
};
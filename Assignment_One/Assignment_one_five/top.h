#pragma once

#include <systemc.h>
#include "slave.h"
#include "master.h"
#include "configuration.h"
#include "inAdapter.h"


SC_MODULE(TOP) {
	
	sc_trace_file* tracefile;

	sc_signal<bool> valCh;
	sc_signal<bool> rdyCh;
	sc_signal<bool> resCh;
	sc_signal<sc_int<DATA_BITS>> dataCh;
	sc_signal<sc_int<CHANNEL_BITS>> bitCh[2];
	sc_signal<sc_int<ERROR_BITS>> errCh;

	sc_clock myClock;

	InAdapter<sc_int<DATA_BITS> > *pInAdapter;
	Master *master;
	Slave *slave;

	SC_CTOR(TOP) {
		sc_clock myClock("clock", sc_time(CLK_PERIOD, SC_NS));

		pInAdapter = new InAdapter<sc_int<DATA_BITS>>("adapter");
		master = new Master("master");
		slave = new Slave("slave");


		master->out(*pInAdapter);

		pInAdapter->clock(myClock);
		slave->clock(myClock);

		pInAdapter->valid(valCh);
		pInAdapter->ready(rdyCh);

		slave->valid(valCh);
		slave->ready(rdyCh);

		for (int i = 0; i < 2; i++)
		{
			pInAdapter->channel(bitCh[i]);
			slave->channel(bitCh[i]);
		}


		pInAdapter->error(errCh);
		slave->error(errCh);

		pInAdapter->data(dataCh);
		slave->data(dataCh);

		//stim.reset(resCh);
		pInAdapter->reset(resCh);
		slave->reset(resCh);
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
			sc_trace(tracefile, bitCh[i], "Channel_bits" + (char)i);
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
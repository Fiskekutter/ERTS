#pragma once
#include <systemc.h>
#include "Stimulus.h"
#include "mac.h"
#include "monitor.h"



SC_MODULE(TOP) {
	sc_signal<int> siga, sigb, sigc;
	sc_clock(myClock);

	sc_trace_file *tracefile;

	STIMULUS Stim;
	MAC Mac;
	MONITOR Mon;
	
	SC_CTOR(TOP):myClock("myClock"), Stim("stim"), Mac("mac"), Mon("mon") 
	{
		sc_clock("clock", sc_time(20, SC_NS));

		Stim.a(siga);
		Stim.b(sigb);
		Stim.clk(myClock);

		Mac.a(siga);
		Mac.b(sigb);
		Mac.c(sigc);
		
		Mon.c(sigc);
	

	}

	void start_of_simulation() {
		tracefile = sc_create_vcd_trace_file("file_name");

		sc_trace(tracefile, siga, "Signal A");
		sc_trace(tracefile, sigb, "Signal B");
		sc_trace(tracefile, sigc, "Signal C");
		sc_trace(tracefile, myClock, "Clk");
	}

	void end_of_simulation() {
		sc_close_vcd_trace_file(tracefile);
	}
};

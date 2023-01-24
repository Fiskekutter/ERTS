// Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#ifdef __RTL_SIMULATION__
#include advios_rtl_wrapper.h
#define advios advios_RTL_wrapper
#else
#include "advios_ip.h"
#endif

#include <iostream>
#include "systemc.h"
#include "stimuli.h"
#include "advios_ip.h"


int sc_main(int argc, char* argv[])
{
	sc_report_handler::set_actions( SC_ID_LOGIC_X_TO_BOOL_, SC_LOG);
	sc_report_handler::set_actions( SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_, SC_LOG);
	sc_report_handler::set_actions( SC_ID_OBJECT_EXISTS_, SC_LOG);
	
	sc_clock clock("clock", 10, SC_NS);
	sc_signal<bool> resetCh("topReset");
	sc_signal<sc_uint<NUM_BITS> > ctrlCh("topCtrl");
	sc_signal<sc_uint<NUM_BITS> > inSwitchCh("topSwitch");
	sc_signal<sc_uint<NUM_BITS> > outLedsCh("topLeds");

	stim Stim("stim");
	advios Advios("advios");

	Advios.reset(resetCh);
	Advios.ctrl(ctrlCh);
	Advios.inSwitch(inSwitchCh);
	Advios.outLeds(outLedsCh);
	Advios.clk(clock);

	Stim.stimReset(resetCh);
	Stim.stimCtrl(ctrlCh);
	Stim.outSwitch(inSwitchCh);
	Stim.inLeds(outLedsCh);
	Stim.stimClk(clock);


	cout << "INFO: Simulating"  << endl;
	sc_start(300, SC_NS);
	cout << "INFO: End of Simulation" << endl;

	return 0;
}

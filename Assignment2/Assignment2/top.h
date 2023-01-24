#pragma once

#include "systemc.h"
#include "advios_ip.h"
#include "stimuli.h"

#define NUM_BITS 4

SC_MODULE(top){
	sc_clock clock;
	sc_signal<bool> resetCh;
	sc_signal<sc_uint<NUM_BITS> > ctrlCh;
	sc_signal<sc_uint<NUM_BITS> > inSwitchCh;
	sc_signal<sc_uint<NUM_BITS> > outLedsCh;

	stim Stim;
	advios Advios;

	SC_CTOR(top) : 
		resetCh("topReset"), 
		ctrlCh("topCtrl"), 
		inSwitchCh("topSwitch"),
		outLedsCh("topLeds"), 
		Stim("stim"), 
		Advios("advios"),
		clock("clock", 10, SC_NS){

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

	}
};

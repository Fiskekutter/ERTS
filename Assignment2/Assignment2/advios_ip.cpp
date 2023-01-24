#include "advios_ip.h"

#define clkSecond 100000000

void advios::secondsCounter(void) {
	while (1) {
		counter++;
		if (counter >= clkSecond) {
			counter = 0;
			second.write(true);
			wait();
			second.write(false);
		}
		wait();
	}
}

void advios::master(void) {
	#pragma HLS resource core=AXI4LiteS metadata="-bus_bundle slv0" variable=ctrl

	while (1) {
		control = ctrl.read();
		switches = inSwitch.read();
		switch (control)
		{
		case 0 :{
			if (second.read()) {
				ledValue++;
				outLeds.write(ledValue);
			}
			break;
		}
		case 8 :{
			ledValue = 0;
			outLeds.write(ledValue);
			break;
		}
		default:
			outLeds.write(control & switches);
			break;
		}
		wait();
	}
}

#include "ModuleSingle.h"


void ModuleSingle::myMethod(void) {
	while (1) {
		myEvent.notify();
		wait(2, SC_MS);
	}
}

void ModuleSingle::myMethod2(void) {
	std::cout << "Counter Value: " << counter++ << std::endl;
	std::cout << "Current Simulation time: " << sc_time_stamp() << std::endl;
}

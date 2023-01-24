#include "ModuleDouble.h"

void ModuleDouble::threadA(void) {
	while (1) {
		cnt = 1;
		eA.notify();
		wait(3, SC_MS, Aack);
	}

}

void ModuleDouble::threadB(void) {
	while (1) {
		cnt = 2;
		eB.notify();
		wait(2, SC_MS, Back);
	}
}

void ModuleDouble::methodA(void) {

	switch (cnt) {
		case 0: cout << sc_time_stamp() << " start" << endl;
			next_trigger(eA | eB);
			break;
		case 1: cout << sc_time_stamp() << " Event A triggered" << endl;
			next_trigger(eB);
			Aack.notify();
			break;
		case 2: cout << sc_time_stamp() << " Event B triggered" << endl;
			next_trigger(eA);
			Back.notify();
		default:
			break;
	}
}
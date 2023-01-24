#pragma
#include <systemc.h>

SC_MODULE(ModuleDouble) {
	sc_event eA, eB, Aack, Back;
	int cnt = 0;

	SC_CTOR(ModuleDouble) {
		SC_THREAD(threadA);
		SC_THREAD(threadB);
		SC_METHOD(methodA);
	}

	void threadA(void);
	void threadB(void);
	void methodA(void);
};
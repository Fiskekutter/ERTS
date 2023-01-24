// TryingStuff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <systemc>
#include <systemc.h>


SC_MODULE(Hello_Systemc) {

	SC_CTOR(Hello_Systemc) {
		SC_THREAD(main_thread);
	}

	void main_thread(void) {
		for (int i = 0; i < 5; i++) {
			SC_REPORT_INFO("", "Hello SystemC World!");
		}
		
	}
};


int sc_main(int sc_argc, char* sc_argv[])
{
    
	//std::cout << "Hello World!\n";
	Hello_Systemc HelloWorld_i("HelloWorld_i");

	sc_start();

	return 0;
}

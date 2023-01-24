// Mac.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "mac.h"
#include "top.h"
#include "monitor.h"
#include "Stimulus.h"

int sc_main(int argc, char* argv[])
{
	TOP top("top");

	top.start_of_simulation();
	sc_start(5000, SC_NS);
	top.end_of_simulation();

	return 0;
}
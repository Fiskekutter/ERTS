// Assignment_one_four.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <systemc.h>
#include "top.h"

int sc_main(int argc, char* argv[])
{
	TOP top("top");
	sc_start(500, SC_NS);

	return 0;
}
#pragma once
#include <systemc.h>
#include "configuration.h"


template <class T>
class InAdapter : public sc_fifo_out_if <T>, public sc_module
{
public: // Clock and reset  
	sc_in_clk clock; // Clock  
	sc_in<bool> reset; // Reset   

	// Handshake ports for ST bus  
	sc_in<bool> ready; // Ready signal  
	sc_out<bool> valid; // Valid signal   

	// Channel, error and data ports ST bus  
	sc_out<sc_int<CHANNEL_BITS> > channel;
	sc_out<sc_int<ERROR_BITS> > error;
	sc_out<sc_int<DATA_BITS> > data;

	void write(const T & value)
	{
		if (reset == SC_LOGIC_0)
		{
			sc_int<16> dataSend = 0;
			int cnt = 0;
			int cc = -1;
			while (1) {
				//wait(clock.posedge_event());
				while (ready->read() == false) {
					wait();
				}
				for (int i = 0; i < READY_LATENCY; i++) {
					wait(clock->posedge_event());
				}
				valid->write(true);
				while (ready->read() == true || cnt < cc + READY_LATENCY) {
					//std::cout << "Data send: " << dataSend << std::endl;
					dataSend = dataSend + 1;
					for (int i = 0; i < channel.size(); i++) {
						channel[i]->write(i);
					}
					error->write(0);
					data->write(dataSend);
					if (ready->read() == true) { cc++; }
					cnt++;
					wait(clock->posedge_event());
					//std::cout << sc_time_stamp() << std::endl;
				}
				valid->write(false);
				cnt = 0;
				cc = -1;

				if (dataSend > 254) { dataSend = 0; }
				//wait(clock.posedge_event());
			//// Output sample data on negative edge of clock       
			//while (ready == SC_LOGIC_0)        
			//wait(clock.posedge_event());  
			//wait(clock.posedge_event());   
			//data.write(value);   
			//channel.write(0); // Channel number   
			//error.write(0); // Error   
			//valid.write(SC_LOGIC_1); // Signal valid new data   
			//wait(clock.posedge_event());   
			//valid.write(SC_LOGIC_0);      
			}
		}
		else wait(clock.posedge_event());
	}

	InAdapter(sc_module_name name_)
		: sc_module(name_)
	{
	}

	private:
		bool nb_write(const T & data) override
		{
			SC_REPORT_FATAL("/InAdapter", "Called nb_write()");
			return false;
		}
		virtual int num_free() const override
		{
			SC_REPORT_FATAL("/InAdapter", "Called num_free()");
			return 0;
		}
		virtual const sc_event& data_read_event() const override
		{
			SC_REPORT_FATAL("/InAdapter", "Called data_read_event()");
			return *new sc_event;
		}
};
#include "master.h"

void Master::sendData(void) {
	sc_int<16> dataSend = 0;
	int cnt = 0;
	int cc = -1;
	while (1) {

		while (reset->read() == true) {
			wait(clock->posedge_event());
		}
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
			if (ready->read() == true) {cc++;}
			cnt++;
			wait(clock->posedge_event());
			//std::cout << sc_time_stamp() << std::endl;
		}
		valid->write(false);
		cnt = 0;
		cc = -1;

		if (dataSend > 254) { dataSend = 0;}
		//wait(clock.posedge_event());
	}
}
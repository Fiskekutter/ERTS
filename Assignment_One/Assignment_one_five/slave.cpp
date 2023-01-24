#include "slave.h"
#include <iostream>
#include <random>

void Slave::receiveData(void) {
	int counter = 0;
	std::random_device seeder;
	std::default_random_engine rng(seeder());
	std::uniform_int_distribution<int> gen(1, 10);

	while (1) {
		counter = gen(rng);
		
		while (reset->read() == true) {
			wait(clock->posedge_event());
		}
		
		while (valid->read() == false) {
			//std::cout << "ready" << std::endl;
			ready->write(true);
			wait(clock->posedge_event());
		}
		for (int i = 0; i <= counter; i++) {
			//std::cout << "Data read: " << data.read() << std::endl;
			for (int i = 0; i < channel.size(); i++) {
				channel[i]->read();
			}
			data->read();
			error->read();
			storeToText();
			wait(clock->posedge_event());
		}
		ready->write(false);
		wait(clock->posedge_event());

		if (data->read() >= 254) {
		}
	}
		
}

void Slave::storeToText(void) {
	ofstream dataFile;
	dataFile.open("dataFile.txt", std::ios::app);
	dataFile << data << "," << endl;
	dataFile.close();
}
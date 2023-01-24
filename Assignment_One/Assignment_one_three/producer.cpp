#include "producer.h"
#include <random>


void producer::produce(void) {
	TCPHeader tPack;
	std::random_device seeder;
	std::default_random_engine rng(seeder());
	std::uniform_int_distribution<int> gen(2, 10);

	while (1) {
		wait(gen(rng), SC_MS);
		tPack.SequenceNumber = tPack.SequenceNumber + 1;
		
		out->write(tPack);
	}
	
}
#include "SRandBasedGenerator.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

SRandBasedGenerator::SRandBasedGenerator() {
	srand(std::time(0));
}

SRandBasedGenerator::~SRandBasedGenerator() {
}

int SRandBasedGenerator::nextInt() {
	return rand();
}

int SRandBasedGenerator::nextInt(int low, int high) {
	return low+(nextInt() % abs(high-low));
}

#pragma once

#include "RandomNumberGenerator.h"

/*
 *
 */
class SRandBasedGenerator : public RandomNumberGenerator {
public:
	SRandBasedGenerator();
	virtual ~SRandBasedGenerator();
	virtual int nextInt();
	virtual int nextInt(int low, int high);
};


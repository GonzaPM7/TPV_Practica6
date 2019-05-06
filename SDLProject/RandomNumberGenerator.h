#pragma once

/*
 *
 */
class RandomNumberGenerator {
public:
	RandomNumberGenerator();
	virtual ~RandomNumberGenerator();
	virtual int nextInt() = 0;
	virtual int nextInt(int low, int high) = 0;
};


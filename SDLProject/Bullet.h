#pragma once

#include "Container.h"

/*
 *
 */
class Bullet: public Container {
public:
	Bullet();
	Bullet(SDLGame *game);
	virtual ~Bullet();
	int getPower() const;
	void setPower(int power);

private:
	int power_;
};


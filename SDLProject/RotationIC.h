#pragma once
#include "InputComponent.h"

/*
 *
 */
class RotationIC : public InputComponent {
public:
	RotationIC();
	RotationIC(SDL_Keycode left, SDL_Keycode right, double angle);
	virtual ~RotationIC();
	virtual void handleInput(Container* c, Uint32 time);
private:
	SDL_Keycode left_;
	SDL_Keycode right_;
	double angle_;

};


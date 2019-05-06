#pragma once
#include "InputComponent.h"

/*
 *
 */
class ThrustIC : public InputComponent {
public:
	ThrustIC();
	ThrustIC(SDL_Keycode ctrlKey);
	virtual ~ThrustIC();
	virtual void handleInput(Container* c, Uint32 time);
private:
	SDL_Keycode ctrlKey_;
};


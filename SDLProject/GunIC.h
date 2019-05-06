#pragma once

#include "InputComponent.h"

/*
 *
 */
class GunIC: public InputComponent {
public:
	GunIC(SDL_Keycode ctrlKey);
	virtual ~GunIC();
	virtual void handleInput(Container* c, Uint32 time);
private:
	SDL_Keycode ctrlKey_;

};


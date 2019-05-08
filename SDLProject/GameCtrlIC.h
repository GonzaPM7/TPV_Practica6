#pragma once

#include "InputComponent.h"

/*
 *
 */
class GameCtrlIC: public InputComponent {
public:
	GameCtrlIC();
	virtual ~GameCtrlIC();
	virtual void handleInput(Container* c, Uint32 time);
private:
};


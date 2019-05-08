#pragma once
#include "GraphicsComponent.h"

/*
 *
 */
class GameStatusViewGC : public GraphicsComponent {
public:
	GameStatusViewGC();
	virtual ~GameStatusViewGC();
	virtual void render(Container* c, Uint32 time);
};


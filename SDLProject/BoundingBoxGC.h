#pragma once

#include "GraphicsComponent.h"

/*
 *
 */
class BoundingBoxGC: public GraphicsComponent {
public:
	BoundingBoxGC();
	BoundingBoxGC(SDL_Color color);
	virtual ~BoundingBoxGC();
	virtual void render(Container* c, Uint32 time);
private:
	SDL_Color color_;
};


#pragma once

#include "Component.h"
#include "Container.h"
#include "sdl_includes.h"

/*
 *
 */
class GraphicsComponent: virtual public Component {
public:
	GraphicsComponent();
	virtual ~GraphicsComponent();
	virtual void render(Container* c, Uint32 time) = 0;
};


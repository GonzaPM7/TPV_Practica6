#pragma once

#include "Container.h"
#include "Messages_decl.h"
#include "sdl_includes.h"


/*
 *
 */
class Component {
public:
	Component();
	virtual ~Component();
	virtual void receive(Container* c, const msg::Message& msg);
};


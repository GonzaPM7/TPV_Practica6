#include "Container.h"

#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "Messages_defs.h"

Container::Container() :
		Container(nullptr) {
}

Container::Container(SDLGame* game) :
		GameObject(game), ic_(), pc_(), gc_() {
}

Container::~Container() {
}

void Container::handleInput(Uint32 time) {
	for (auto ic : ic_) {
		if (ic.active && isActive())
			ic.data->handleInput(this, time);
	}
}

void Container::update(Uint32 time) {
	for (auto pc : pc_) {
		if (pc.active && isActive())
			pc.data->update(this, time);
	}
}

void Container::render(Uint32 time) {
	for (auto gc : gc_) {
		if (gc.active && isActive())
			gc.data->render(this, time);
	}
}

void Container::addC(InputComponent* ic) {
	addC(ic_, ic);
}

void Container::addC(PhysicsComponent* pc) {
	addC(pc_, pc);
}

void Container::addC(GraphicsComponent* gc) {
	addC(gc_, gc);
}

void Container::addOC(Component* oc) {
	addC(oc_, oc);
}

bool Container::hasC(InputComponent* ic) {
	return hasC(ic_, ic);
}

bool Container::hasOC(Component* oc) {
	return hasC(oc_, oc);
}

bool Container::hasC(PhysicsComponent* pc) {
	return hasC(pc_, pc);
}

bool Container::hasC(GraphicsComponent* gc) {
	return hasC(gc_, gc);
}

void Container::removeC(InputComponent* ic) {
	removeC(ic_, ic);
}

void Container::removeC(PhysicsComponent* pc) {
	removeC(pc_, pc);
}

void Container::removeC(GraphicsComponent* gc) {
	removeC(gc_, gc);
}

void Container::removeOC(Component* oc) {
	removeC(oc_, oc);
}

void Container::receive(const void* senderObj, const msg::Message& msg) {
	broadcastToLocalComponents(senderObj, msg);
}

void Container::broadcastToLocalComponents(
		const void* senderObj, const msg::Message& msg) {
	for (auto ic : ic_) {
		if (ic.data != senderObj && ic.active)
			ic.data->receive(this, msg);
	}

	for (auto pc : pc_) {
		if (pc.data != senderObj && pc.active)
			pc.data->receive(this, msg);
	}

	for (auto gc : gc_) {
		if (gc.data != senderObj && gc.active)
			gc.data->receive(this, msg);
	}

	for (auto oc : oc_) {
		if (oc.data != senderObj && oc.active)
			oc.data->receive(this, msg);
	}

}

void Container::localSend(const void* senderObj, const msg::Message& msg) {
	broadcastToLocalComponents(senderObj, msg);
}

void Container::globalSend(const void* senderObj, const msg::Message& msg) {
	getGame()->send(senderObj,msg);
}

void Container::reset() {
	ic_.clear();
	pc_.clear();
	gc_.clear();
	oc_.clear();
}



#include "BroadCastObjectInfoPC.h"
#include "Messages_defs.h"

BroadCastObjectInfoPC::BroadCastObjectInfoPC() {
}

BroadCastObjectInfoPC::~BroadCastObjectInfoPC() {
}

void BroadCastObjectInfoPC::update(Container* c, Uint32 time) {
	c->globalSend(this,
			msg::RemoteObjectInfo(c->getId(), msg::Broadcast, c->getPosition(), c->getVelocity(), c->getRotation()));
}

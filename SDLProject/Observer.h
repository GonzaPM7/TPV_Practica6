#pragma once
#include "Messages_decl.h"

/*
 *
 */
class Observer {
public:
	Observer();
	virtual ~Observer();

	msg::ObjectId getId();
	void setId(msg::ObjectId id);

	virtual void receive(const void* senderObj, const msg::Message& msg) = 0;

private:
	msg::ObjectId id_;
};


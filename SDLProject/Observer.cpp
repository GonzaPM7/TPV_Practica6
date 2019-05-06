#include "Observer.h"

Observer::Observer() : id_(msg::None) {
}

Observer::~Observer() {
}

msg::ObjectId Observer::getId() {
	return id_;
}

void Observer::setId(msg::ObjectId id) {
	id_ = id;
}

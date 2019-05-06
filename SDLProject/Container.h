#pragma once

#include "GameObject.h"

class Component;
class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

/*
 *
 */
class Container: public GameObject {
public:
	Container();
	Container(SDLGame* game);
	virtual ~Container();

	virtual void handleInput(Uint32 time);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	void addC(InputComponent* ic);
	void addC(PhysicsComponent* pc);
	void addC(GraphicsComponent* gc);
	void addOC(Component* oc); // add observer component, just to receive messages

	bool hasC(InputComponent* ic);
	bool hasC(PhysicsComponent* pc);
	bool hasC(GraphicsComponent* gc);
	bool hasOC(Component* oc);

	void removeC(InputComponent* ic);
	void removeC(PhysicsComponent* pc);
	void removeC(GraphicsComponent* gc);
	void removeOC(Component* oc);


	void reset(); // removes all components

	virtual void receive(const void* senderObj, const msg::Message& msg);

	// used by components to send message at the level of container
	void localSend(const void* senderObj, const msg::Message& msg);

	// this will be used by components to send message globally
	void globalSend(const void* senderObj, const msg::Message& msg);
private:
	void broadcastToLocalComponents(const void* senderObj, const msg::Message& msg);

	template<typename T>
	struct wrapper {
		bool active;
		T* data;

		bool operator==(const wrapper<T>& other) const {
			return other.data == data;
		}
	};

	template<typename T>
	void addC(vector<wrapper<T>> &v, T* c);

	template<typename T>
	bool hasC(vector<wrapper<T>> &v, T* c);

	template<typename T>
	void removeC(vector<wrapper<T>> &v, T* c);

	vector<wrapper<InputComponent>> ic_;
	vector<wrapper<PhysicsComponent>> pc_;
	vector<wrapper<GraphicsComponent>> gc_;
	vector<wrapper<Component>> oc_;
};

template<typename T>
inline void Container::addC(vector<wrapper<T>> &v, T* c) {

	if (c == nullptr)
		return;

	wrapper<T> r = { true, c };

	auto position = std::find(v.begin(), v.end(), r);

	if (position != v.end()) {
		(*position).active = true;
	} else {
		v.push_back(r);
	}
}

template<typename T>
inline bool Container::hasC(vector<wrapper<T>> &v, T* c) {
	wrapper<T> r = { true, c };
	auto position = std::find(v.begin(), v.end(), r);

	return position != v.end();
}

template<typename T>
inline void Container::removeC(vector<wrapper<T>> &v, T* c) {
	if (c == nullptr)
		return;

	wrapper<T> r = { true, c };
	auto position = std::find(v.begin(), v.end(), r);

	if (position != v.end()) {
		(*position).active = false;
	}
}

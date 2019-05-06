#pragma once

#include "Container.h"
#include <array>

/*
 *
 */
template<typename T, int SIZE>
class GameObjectPool: public Container {
public:
	GameObjectPool(SDLGame* game);
	virtual ~GameObjectPool();
	virtual void handleInput(Uint32 time);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	T* getUnusedObject();
	const vector<T*>& getAllObjects();
	void deactiveAllObjects();

private:
	array<T, SIZE> objs_;
	vector<T*> objsPointers_;
};

template<typename T, int SIZE>
inline GameObjectPool<T, SIZE>::GameObjectPool(SDLGame* game) :
		Container(game), objs_() {
	for (auto &o : objs_) {
		o.setActive(false);
		o.setGame(game);
		o.init();
		objsPointers_.push_back(&o);
	}
}

template<typename T, int SIZE>
inline GameObjectPool<T, SIZE>::~GameObjectPool() {
}

template<typename T, int SIZE>
inline void GameObjectPool<T, SIZE>::handleInput(Uint32 time) {
	Container::handleInput(time);
	if (!isActive())
		return;
	for (auto &o : objs_) {
		if (o.isActive()) {
			o.handleInput(time);
		}
	}
}

template<typename T, int SIZE>
inline void GameObjectPool<T, SIZE>::update(Uint32 time) {
	Container::update(time);
	if (!isActive())
		return;
	for (auto &o : objs_) {
		if (o.isActive()) {
			o.update(time);
		}
	}
}

template<typename T, int SIZE>
inline void GameObjectPool<T, SIZE>::render(Uint32 time) {
	Container::render(time);
	if (!isActive())
		return;
	for (auto &o : objs_) {
		if (o.isActive()) {
			o.render(time);
		}
	}
}

template<typename T, int SIZE>
inline T* GameObjectPool<T, SIZE>::getUnusedObject() {
	for (auto &o : objs_) {
		if (!o.isActive()) {
			return &o;
		}
	}

	return nullptr;
}

template<typename T, int SIZE>
inline const vector<T*>& GameObjectPool<T,SIZE>::getAllObjects() {
	return objsPointers_;
}

template<typename T, int SIZE>
inline void GameObjectPool<T,SIZE>::deactiveAllObjects() {
	for (auto &o : objs_) {
		o.setActive(false);
	}
}

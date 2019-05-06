#pragma once

#include "SDLGame.h"
#include "Vector2D.h"
#include "Observer.h"


class GameObject : public Observer {

public:
	GameObject();
	GameObject(SDLGame* game);
	virtual ~GameObject();

	SDLGame* getGame() const;
	void setGame(SDLGame* game);

	bool isActive() const;
	void setActive(bool active);
	bool toggleActive();

	double getWidth() const;
	void setWidth(double width);

	double getHeight() const;
	void setHeight(double height);

	void scale(double s);

	Vector2D getPosition() const;
	void setPosition(const Vector2D &pos);

	Vector2D getVelocity() const;
	void setVelocity(const Vector2D &vel);

	Vector2D getAcceleration() const;
	void setAcceleration(const Vector2D &vel);

	double getRotation() const;
	void setRotation(double angle);

	virtual void receive(const void* senderObj, const msg::Message& msg);

	// some GameObjects cannot be initialized in the constructor,
	// for example when we create them using the default constructor
	// and without passing the game. This method is supposed to
	// be called once they are ready to be initialized. The
	// default implementation does nothing.
	virtual void init();

	// abstract methods to be implemented in sub-classes
	virtual void handleInput(Uint32 time) = 0;
	virtual void update(Uint32 time) = 0;
	virtual void render(Uint32 time) = 0;

protected:
	SDLGame* game_; // pointer to the game

	bool active_;   // indicates if the object is active

	double width_;  // width
	double height_; // height

	Vector2D position_; // position (suppose to be left-top corner)
	Vector2D velocity_; // velocity
	Vector2D acceleration_; // acceleration
	double rotation_; // rotation (for the corresponding texture)
};

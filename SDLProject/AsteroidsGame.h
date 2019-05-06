#pragma once

#include <vector>

#include "Bullets.h"
#include "Fighter.h"
#include "SDLGame.h"
#include "GameObject.h"

class AsteroidsGame: public SDLGame {

public:
	AsteroidsGame();
	virtual ~AsteroidsGame();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	const static int _WINDOW_WIDTH_ = 800;
	const static int _WINDOW_HEIGHT_ = 600;
	bool exit_;
	std::vector<GameObject*> actors_;

	Bullets bulletsShooter_;
	Fighter fighter0_;
};

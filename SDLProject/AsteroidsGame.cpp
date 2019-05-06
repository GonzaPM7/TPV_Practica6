#include "AsteroidsGame.h"

#include "InputHandler.h"
using namespace std;

AsteroidsGame::AsteroidsGame() :
		SDLGame("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_), bulletsShooter_(
				this), fighter0_(msg::Fighter_0,this) {
	initGame();
}

AsteroidsGame::~AsteroidsGame() {
	closeGame();
}

void AsteroidsGame::initGame() {

	addObserver(&bulletsShooter_);
	addObserver(&fighter0_);

	actors_.push_back(&fighter0_);
	actors_.push_back(&bulletsShooter_);
}

void AsteroidsGame::closeGame() {
}

void AsteroidsGame::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();

		handleInput(startTime);
		update(startTime);
		render(startTime);

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void AsteroidsGame::stop() {
	exit_ = true;
}

void AsteroidsGame::handleInput(Uint32 time) {

	InputHandler::instance()->update();

	// full screen
	if (InputHandler::instance()->isKeyDown(SDLK_f)) {
		int flags = SDL_GetWindowFlags(window_);
		if (flags & SDL_WINDOW_FULLSCREEN) {
			SDL_SetWindowFullscreen(window_, 0);
		} else {
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
		}
	}

	// stop
	if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
		stop();
	}

	for (GameObject* o : actors_) {
		o->handleInput(time);
	}
}

void AsteroidsGame::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void AsteroidsGame::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(getRenderer());

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}


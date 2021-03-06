#include "AsteroidsGame.h"

#include "InputHandler.h"
using namespace std;

AsteroidsGame::AsteroidsGame() :
		SDLGame("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_), bulletsShooter_(
				this), fighter0_(msg::Fighter_0,this), fighter1_(msg::Fighter_1, this), networkMessenger_(this), gameManager_(this) {
	initGame();
}

AsteroidsGame::~AsteroidsGame() {
	closeGame();
}

void AsteroidsGame::initGame() {

	addObserver(&bulletsShooter_);
	addObserver(&fighter0_);
	addObserver(&fighter1_);
	addObserver(&networkMessenger_);
	addObserver(&gameManager_);

	actors_.push_back(&fighter0_);
	actors_.push_back(&fighter1_);
	actors_.push_back(&bulletsShooter_);
	actors_.push_back(&gameManager_);
}

void AsteroidsGame::closeGame() {
}

void AsteroidsGame::start() {
	send(this, msg::Message(msg::PALYER_CONNECTED, msg::None, msg::Broadcast));
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();

		networkMessenger_.update();
		handleInput(startTime);
		update(startTime);
		render(startTime);

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
	send(this, msg::Message(msg::PALYER_DISCONNECTED, msg::None, msg::Broadcast));
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


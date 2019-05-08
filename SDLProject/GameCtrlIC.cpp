#include "GameCtrlIC.h"
#include "GameManager.h"
#include "Messages_defs.h"
#include "InputHandler.h"

GameCtrlIC::GameCtrlIC() {
}

GameCtrlIC::~GameCtrlIC() {
}

void GameCtrlIC::handleInput(Container* c, Uint32 time) {

	GameManager* gm = static_cast<GameManager*>(c);

	// if any key pressed while not running, we choose a random velocity of the ball
	if (gm->getStatus() == GameManager::READY
			&& InputHandler::instance()->anyKeyDown()) {

		gm->globalSend(this,
				msg::Message(msg::START_GAME_REQUEST, c->getId(),
						msg::Broadcast));

	}
}

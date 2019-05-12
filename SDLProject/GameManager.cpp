#include "GameManager.h"

#include "ClientInfo.h"
#include "Messages_defs.h"
GameManager::GameManager(SDLGame *game) : Container(game) {

  status_ = WAITING;
  numOfConnectPlayers_ = 1;
  playersStatus[ClientInfo::instance()->getClientId()] = true;
  winner_ = -1;

  setId(msg::GameManager);
  addC(&gameStatusGC_);
  addC(&gameCtrl_);
  if ((ClientInfo::instance()->getClientId() == 0)) {
    addC(&bulletsFighterCollision_);
  }
}

GameManager::~GameManager() {}

GameManager::GameStatus GameManager::getStatus() { return status_; }

void GameManager::setStatus(GameManager::GameStatus s) { status_ = s; }

void GameManager::receive(const void *senderObj, const msg::Message &msg) {
  Container::receive(senderObj, msg);
  switch (msg.type_) {
  case msg::PALYER_CONNECTED:
    handlePlayerConnected(msg);
    break;
  case msg::PALYER_DISCONNECTED:
    handlePlayerDisConnected(msg);
    break;
  case msg::PLAYER_INFO:
    handlePlayerInfo(msg);
    break;
  case msg::STOP_GAME:
    handleStopGame(msg);
    break;
  case msg::GAME_IS_READY:
    handleGameIsReady(msg);
    break;
  case msg::START_GAME_REQUEST:
    handleStartGameRequest(msg);
    break;
  case msg::GAME_START:
    handleGameStart(msg);
    break;
  case msg::FIGHTER_BULLET_COLLISION:
    handleFighterBulletCollision0(msg);
    break;
  case msg::GAME_OVER:
    handleFighterBulletCollision1(msg);
    break;
  default:
    break;
  }
}

void GameManager::handlePlayerInfo(const msg::Message &msg) {

  // if the player is not marked as connected already we mark it
  // and increase the number of connected players
  if (!playersStatus[msg.clientId_]) {
    playersStatus[msg.clientId_] = true;
    numOfConnectPlayers_++;
  }

  // if all are connected and it is the master client,
  // we send a message telling that the game is ready
  if (ClientInfo::instance()->isMaster() &&
      numOfConnectPlayers_ == NUM_OF_PLAYERS_) {
    setStatus(GameManager::READY);
    globalSend(this, msg::Message(msg::GAME_IS_READY, getId(), msg::Broadcast));
  }
}

void GameManager::handlePlayerConnected(const msg::Message &msg) {
  // when someone connects, all reply with their info so the new player can
  // get it
  globalSend(this, msg::Message(msg::PLAYER_INFO, getId(), msg::Broadcast));
}

void GameManager::handlePlayerDisConnected(const msg::Message &msg) {
  // if the player is not marked as disconnected already we mark it
  // and decrease the number of connected players, set game state to waiting,
  // etc.
  if (playersStatus[msg.clientId_]) {
    playersStatus[msg.clientId_] = false;
    numOfConnectPlayers_--;
    setStatus(GameManager::WAITING);
    winner_ = -1;

    // if I am the master, I tell everyone to sop the game
    if (ClientInfo::instance()->isMaster())
      globalSend(this, msg::Message(msg::STOP_GAME, getId(), msg::Broadcast));

    // if the one who has disconnected is the MASTER, we exit the game
    if (ClientInfo::instance()->isMaster(msg.clientId_)) {
      getGame()->stop();
    }
  }
}

void GameManager::handleStopGame(const msg::Message &msg) {
  // someone has disconnected, so we put the game back into WAITING state
  setStatus(GameManager::WAITING);
  winner_ = -1;
}

void GameManager::handleGameIsReady(const msg::Message &msg) {
  setStatus(GameManager::READY);
}

void GameManager::handleStartGameRequest(const msg::Message &msg) {
  // if a player request to start, and the game is READY, the master tells
  // everybody to start
  if (ClientInfo::instance()->isMaster() && status_ == GameManager::READY) {
    status_ = GameManager::RUNNING;
    globalSend(this, msg::Message(msg::GAME_START, getId(), msg::Broadcast));
  }
}

void GameManager::handleGameStart(const msg::Message &msg) {
  status_ = GameManager::RUNNING;
}

void GameManager::handleFighterBulletCollision0(const msg::Message &msg) {
	if ((ClientInfo::instance()->getClientId() == 0)) {
		if (static_cast<const msg::FighterBulletCollisionMsg &>(msg)
			.fighter_->getId() == msg::Fighter_0)
			winner_ = 0;
		else
			winner_ = 1;

		setStatus(GameStatus::READY);
		globalSend(
			this,
			msg::Message(msg::GAME_OVER,
				static_cast<const msg::FighterBulletCollisionMsg &>(msg)
				.fighter_->getId(),
				msg::Broadcast));
	}
}

void GameManager::handleFighterBulletCollision1(const msg::Message &msg) {
	if ((ClientInfo::instance()->getClientId() == 0)) {
		if (static_cast<const msg::FighterBulletCollisionMsg &>(msg)
			.fighter_->getId() == msg::Fighter_0)
			winner_ = 0;
		else
			winner_ = 1;

		setStatus(GameStatus::READY);
	}
}

  int GameManager::getWinner() { return winner_; }

#pragma once

#include "Container.h"
#include "GameCtrlIC.h"
#include "GameStatusViewGC.h"

/*
 *
 */
class GameManager: public Container {
public:
	enum GameStatus { WAITING, READY, RUNNING};

	GameManager(SDLGame* game);
	virtual ~GameManager();

	GameStatus getStatus();
	void setStatus(GameStatus s);
	int getWinner();
	void receive(const void* senderObj, const msg::Message& msg);

private:
	void handlePlayerInfo(const msg::Message& msg);
	void handlePlayerDisConnected(const msg::Message& msg);
	void handlePlayerConnected(const msg::Message& msg);
	void handleStopGame(const msg::Message& msg);
	void handleGameIsReady(const msg::Message& msg);
	void handleStartGameRequest(const msg::Message& msg);
	void handleGameStart(const msg::Message& msg);

	GameStatusViewGC gameStatusGC_;
	GameCtrlIC gameCtrl_;
	GameStatus status_;
	const static int NUM_OF_PLAYERS_ = 2;
	int numOfConnectPlayers_;
	bool playersStatus[NUM_OF_PLAYERS_];
	int winner_;
};


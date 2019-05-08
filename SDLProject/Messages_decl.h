#pragma once

namespace msg {

enum ObjectId {
	None,  	// special value indicating no object (or more precisely component)
	Broadcast,   // special value indicating all objects
	Fighter_0,
	Fighter_1,
	Bullets,
	GameManager,
	Server
};

enum MessageType {
	GAME_START,
	GAME_OVER,
	FIGHTER_SHOOT,
	CONNECTED,
	REMOTE_OBJ_INFO,
	SCORE_UPDATED,
	PALYER_CONNECTED,
	PALYER_DISCONNECTED,
	GAME_IS_READY,
	STOP_GAME,
	PLAYER_INFO,
	START_GAME_REQUEST,
};

struct Message;
typedef int header_t_;

};

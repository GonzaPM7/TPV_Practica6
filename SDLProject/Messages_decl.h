#pragma once

namespace msg {

enum ObjectId {
	None,  	// special value indicating no object (or more precisely component)
	Broadcast,   // special value indicating all objects
	Fighter_0,
	Fighter_1,
	Asteroids,
	Bullets,
	GameManager,
	Server
};

enum MessageType {
	GAME_START,
	GAME_OVER,
	ROUND_START,
	ROUND_OVER,
	FIGHTER_SHOOT,
	BULLET_ASTEROID_COLLISION,
	FIGHTER_ASTEROID_COLLISION,
	ASTEROID_DESTROYED,
	NO_MORE_ASTEROIDS,
	FIGHTER_INFO,
	BULLETS_INFO,
	ASTEROIDS_INFO,

	// for network game
	CONNECTED,
	REMOTE_OBJ_INFO,
	SCORE_UPDATED
};

struct Message;
typedef int header_t_;

};

#include "Bullet.h"

Bullet::Bullet() : Bullet(nullptr) {
}

Bullet::Bullet(SDLGame* game) : Container(game), power_(0) {
}

Bullet::~Bullet() {
}

int Bullet::getPower() const {
	return power_;
}

void Bullet::setPower(int power) {
	power_ = power;
}

#include "BulletsFighterCollision.h"
#include "GameManager.h"
#include "Collisions.h"
#include "Messages_defs.h"

BulletsFighterCollision::BulletsFighterCollision()
{
}


BulletsFighterCollision::~BulletsFighterCollision()
{
}

void BulletsFighterCollision::update(Container * c, Uint32 time)
{
	GameManager* gm = static_cast<GameManager*>(c);

	bool collision = false;

	if (gm->getStatus() == GameManager::RUNNING)
	{
		if (fighter_ != nullptr && bullets_ != nullptr)
		{
			auto it = bullets_->begin();

			while (it != bullets_->end() && !collision)
			{
				if (fighter_->isActive() && (*it)->isActive() && Collisions::collidesWithRotation(fighter_, (*it)))
				{
					// enviar mensaje
					c->globalSend(this, msg::FighterBulletCollisionMsg(msg::None, msg::Broadcast, fighter_, (*it)));
					collision = true;
				}
				it++;
			}
		}
	}
}

void BulletsFighterCollision::receive(Container * c, const msg::Message & msg)
{
	switch (msg.type_)
	{
	case msg::BULLETS_INFO:
	{
		bullets_ = static_cast<const msg::BulletsInfoMsg&>(msg).bullets_;
	}
	break;
	case msg::FIGHTER_INFO:
		fighter_ = static_cast<const msg::FighterInfo&>(msg).fighter_;
		break;

	}
}

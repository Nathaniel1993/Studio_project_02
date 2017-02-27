#include "Bullet.h"

Bullet::Bullet(Vector3 OriginPos,Player PlayerRef)
{
	this->setPosition(OriginPos);
	distance = PlayerRef.getPosition() - this->getPosition();
}

Bullet::~Bullet()
{

}

void Bullet::Update(double _dt, Player *playerRef)
{
	TimeToDecay += _dt;
	this->position_ += distance * _dt * 1.0f;
	//std::cout << position_ << std::endl;
	if ((this->getPosition() - playerRef->getPosition()).Length() <= 5)
	{
		playerRef->setPlayerShield(playerRef->getCurrentShield() - 1);
		playerHit = true;
		if (playerRef->getCurrentShield() <= 0 && playerHit)
		{
			playerRef->setPlayerHealth(playerRef->getCurrentHealth() - 1);
			//playerHit = true;
		}
		if (playerRef->getCurrentHealth() <= 0)
		{
			playerRef->isDead();
		}
	}
	else
	{
		playerHit = false;
	}
	
}
#include "Bullet.h"

Bullet::Bullet(Vector3 OriginPos, Player PlayerRef)
{
	this->setPosition(OriginPos);
	distance = PlayerRef.getPosition() - this->getPosition();
}

Bullet::~Bullet()
{

}

void Bullet::Update(double _dt, Player *playerRef)
{
	TimeToDecay += (float)_dt;
	this->position_ += distance * (float)_dt * 1.0f;
	//std::cout << position_ << std::endl;
	if ((this->getPosition() - playerRef->getPosition()).Length() <= 5)
	{
		playerHit = true;
		playerRef->isHit();
	}
	else
	{
		playerHit = false;
	}

}
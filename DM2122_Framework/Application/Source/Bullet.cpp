#include "Bullet.h"

Bullet::Bullet(Vector3 OriginPos,Camera3 PlayerRef)
{
	this->setPosition(OriginPos);
	distance = PlayerRef.target - this->getPosition();
}

Bullet::~Bullet()
{

}

void Bullet::Update(double _dt, Camera3 playerRef)
{
	TimeToDecay += _dt;
	this->position_ += distance * _dt * 1.0f;
	//std::cout << position_ << std::endl;
	if ((this->getPosition() - playerRef.target).Length() <= 5)
	{
		playerHit = true;
	}
	else
	{
		playerHit = false;
	}
}
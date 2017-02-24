#include "Bullet.h"

Bullet::Bullet(Vector3 OriginPos,Player PlayerRef)
{
	this->setPosition(OriginPos);
	distance = PlayerRef.getPosition() - this->getPosition();
}

Bullet::~Bullet()
{

}

void Bullet::Update(double _dt, Player playerRef)
{
	TimeToDecay += _dt;
	this->position_ += distance * _dt * 1.0f;
	//std::cout << position_ << std::endl;
	if ((this->getPosition() - playerRef.getPosition()).Length() <= 5)
	{
		playerHit = true;
	}
	else
	{
		playerHit = false;
	}
}
#include "Character.h"

Character::Character()
{

}

Character::~Character()
{

}

void Character::SetPosition(Vector3 newPosition)
{
	position_ = newPosition;
}

Vector3 Character::getPosition()
{
	return position_;
}

void Character::addHealth(int addedHealth)
{
	Health += addedHealth;
	if (Health >= 100)
	{
		Health = 100;
	}
}

void Character::getHit(int DMG)
{
	Health -= DMG;
	this->isDead();
}

int Character::getCurrentHP()
{
	return Health;
}

bool Character::isDead()
{
	if (getCurrentHP() <= 0)
	{
		Health = 0;
		return true;
	}
	else
	{
		return false;
	}
}
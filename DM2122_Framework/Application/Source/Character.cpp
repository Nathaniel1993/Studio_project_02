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

void Character::setCurrentHP(int newHealth)
{
	newHealth = Health;
}

int Character::getCurrentHP()
{
	return Health;
}

bool Character::isDead()
{
	if (getCurrentHP() <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

int Player::getCurrentShield()
{
	return shield;
}

int Player::getWeaponDMG()
{
	return weapon_->getAttackDMG();
}

void Player::recieveDamage(int Damage)
{
	int tempHealth = this->getCurrentHP() - Damage;
	setCurrentHP(tempHealth);
}

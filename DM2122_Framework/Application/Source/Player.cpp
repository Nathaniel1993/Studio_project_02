#include "Player.h"

Player::Player()
{
}

Player::~Player()
{

}
void Player::setPlayerHealth(int Hp)
{
	health = Hp;
}
void Player::setPlayerShield(int Sp)
{
	shield = Sp;
}
void Player::setPlayerAbility(int Ap)
{
	ability = Ap;
}
int Player::getCurrentShield()
{
	return shield;
}
int Player::getCurrentHealth()
{
	return health;
}
int Player::getCurrentAbility()
{
	return ability;
}

int Player::getWeaponDMG()
{
	return weapon_->getAttackDMG();
}

void Player::ShieldRegen(float Rate)
{
	
}
void Player::isDead()
{
	//set game over 
	std::cout << "dead" << std::endl;
}

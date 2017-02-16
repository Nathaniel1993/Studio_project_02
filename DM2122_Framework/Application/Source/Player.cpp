#include "Player.h"

Player::Player()
{
	Health = 100;
	shield = 100;
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

void Player::ShieldRegen(float Rate)
{
	if (isInvulnerable_ != true)
	{
		while (shield < 100)
		{
			shield * Rate;
		}
	}
}

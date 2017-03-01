#include "Player.h"
#include "SceneManager.h"
#include "SceneEnd.h"

Player::Player()
{
}

Player::~Player()
{

}

void Player::setPlayerHealth(int Hp)
{
	health = Hp;
	if (health > 5)
	{
		health = 5;
	}
}

void Player::setPlayerShield(int Sp)
{
	shield = Sp;
	if (shield > 5)
	{
		shield = 5;
	}
}

void Player::setPlayerAbility(int Ap)
{
	ability = Ap;
	if (ability > 5)
	{
		ability = 5;
	}
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

void Player::AbilityUpdate()
{
	if (isInvisible == true || isInvulnerable_ == true)
	{
		if (AbilityTimeTaken == false)
		{
			AbilityDuration += ElapsedTime;
			AbilityTimeTaken = true;
		}
		else
		{
			if (ElapsedTime >= AbilityDuration)
			{
				if (isInvulnerable_ == true)
				{
					isInvulnerable_ = false;
				}
				else if (isInvisible == true)
				{
					isInvisible = false;
				}
				AbilityTimeTaken = false;
				AbilityDuration = 0;
			}
		}
	}
}

void Player::ShieldRegen(double _dt)
{
	ElapsedTime += _dt;
	if (getCurrentShield() < 5 && ShieldRegenerating == false)
	{
		ShieldTimeLimit = ElapsedTime + 6;
		ShieldRegenerating = true;
	}
	else if (getCurrentShield() < 5 && ShieldRegenerating == true)
	{
		if (ElapsedTime >= ShieldTimeLimit)
		{
			shield++;
			if (getCurrentShield() == 5)
			{
				ShieldRegenerating = false;
			}
			ShieldTimeLimit = ElapsedTime + 1;
		}
	}
}

void Player::isDead()
{
	SceneEnd::isDead = true;
	SceneManager::SetNextSceneID(6);
}

void Player::isHit()
{
	if (!isInvulnerable_)
	{
		ShieldRegenerating = false;

		if (getCurrentShield() > 0)
		{
			setPlayerShield(getCurrentShield() - 1);
		}
		else
		{
			setPlayerHealth(getCurrentHealth() - 1);
			Score::lostlive = true;
		}

		if (getCurrentHealth() <= 0)
		{
			isDead();
		}

		AbilityDuration = 1;
		isInvulnerable_ = true;
	}
}

void Player::Phase()
{
	if (AbilityDuration <= 0)
	{
		isInvulnerable_ = true;
		AbilityDuration = 4;
		setPlayerAbility(getCurrentAbility() - 1);
	}
}

void Player::Dash()
{

}

void Player::Invis()
{
	if (AbilityDuration <= 0)
	{
		isInvisible = true;
		AbilityDuration = 10;
		setPlayerAbility(getCurrentAbility() - 1);
	}
}

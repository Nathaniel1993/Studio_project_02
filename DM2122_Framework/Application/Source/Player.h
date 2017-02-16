#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Weapon.h"

class Player : public Character
{
public:
	//Constructor & Destructor
	Player();
	~Player();
	//Functions
	int getCurrentShield();
	int getWeaponDMG();
	void ShieldRegen(float Rate = 1.0f);

protected:
	int shield;
	bool isInvulnerable_;
	Weapon* weapon_;
};

#endif // !PLAYER_H

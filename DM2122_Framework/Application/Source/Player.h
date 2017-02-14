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
	void recieveDamage(int Damage);

protected:
	int shield;
	float speed;
	Weapon* weapon_;
};

#endif // !PLAYER_H

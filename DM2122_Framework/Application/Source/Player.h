#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Weapon.h"
#include <vector>


class Player : public Character
{
public:
	//Constructor & Destructor
	Player();
	~Player();
	//Functions
	int getCurrentShield();
	int getCurrentHealth();
	int getCurrentAbility();
	void setPlayerHealth(int Hp);
	void setPlayerShield(int Sp);
	void setPlayerAbility(int Ap);	

	int getWeaponDMG();
	void ShieldRegen(float Rate = 1.0f);
	float healthIconVecX;
	float shieldIconVecX;
	float abilityIconVecX;
	

protected:
	
	int health = 5;
	int shield = 5;
	int ability = 5;

	bool isInvulnerable_;		
		Weapon* weapon_;			
};								
#endif // !PLAYER_H

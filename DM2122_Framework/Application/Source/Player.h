#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Weapon.h"
#include <vector>


class Player : public GameObject
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
	void isDead();


	int getWeaponDMG();
	void ShieldRegen(float Rate = 1.0f);
	float healthIconVecX;
	float shieldIconVecX;
	float abilityIconVecX;
	
	
protected:
	
	unsigned int health = 5;
	unsigned int shield = 5;
	unsigned int ability = 5;

	bool isInvulnerable_;		
		Weapon* weapon_;			
};								
#endif // !PLAYER_H

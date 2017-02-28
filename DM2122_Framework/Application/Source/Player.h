#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
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

	void AbilityUpdate();
	void ShieldRegen(double _dt);
	void isDead();
	void isHit();
	void Phase();
	void Dash();
	void Invis();
	
	float healthIconVecX;
	float shieldIconVecX;
	float abilityIconVecX;

	float AbilityDuration = 0;

	bool isInvisible = false;

protected:
	unsigned int health = 5;
	unsigned int shield = 5;
	unsigned int ability = 5;;

	//Shield
	float ElapsedTime = 0;
	float ShieldTimeLimit = 0;
	float AbilityTimeLimit = 0;

	bool isInvulnerable_ = false;
	bool ShieldRegenerating = false;
	bool AbilityTimeTaken = false;
};
#endif // !PLAYER_H

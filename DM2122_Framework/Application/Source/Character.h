#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
public:
	//Constructor & Destructor
	Character();
	~Character();
	void SetPosition(Vector3 newPosition);
	Vector3 getPosition();
	int getCurrentHP();
	void addHealth(int addedHealth);
	void getHit(int DMG);
	bool isDead();

protected:
	int Health;
};

#endif // !CHARACTER_H

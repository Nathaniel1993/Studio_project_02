#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Camera3.h"
#include "Player.h"

class Bullet : public GameObject
{
public:
	Bullet(Vector3 OriginPos, Player PlayerRef);
	~Bullet();
	void Update(double, Player*);
	float TimeToDecay = 0;
	bool playerHit = false;
	float BULLET_ROTATE = 0;


private:
	Vector3 distance;
};

#endif // !BULLET_H

#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Camera3.h"

class Bullet : public GameObject
{
public:
	Bullet(Vector3 OriginPos, Camera3 PlayerRef);
	~Bullet();
	void Update(double _dt);
	float TimeToDecay = 0;

private:
	Vector3 distance;
};

#endif // !BULLET_H

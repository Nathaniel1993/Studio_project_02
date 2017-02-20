#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Camera3.h"

class Enemy : public GameObject
{
public:
	Enemy(Vector3 newPos, int EnemSizeX, int EnemSizeZ);
	~Enemy();
	void AI(double _dt);
	void DetectingPlayer();
	void Animation(double _dt);
	void PlayerPosUpdate(Camera3 NewPos);

	float ANIM_ROTATE = 0.f; //E01_Rotation
	float ENEMY_TURN = 0.f; //E01_RotationFace

private:
	bool DetectedPlayer = false;

	Camera3 PlayerRef;
};

#endif // !ENEMY_H

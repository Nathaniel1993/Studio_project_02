#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Camera3.h"
#include "Bullet.h"
#include <math.h>

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(Vector3 newPos, float EnemSizeX, float EnemSizeZ);
	~Enemy();

	void Update(double TimeIntake, std::vector<Enemy> OtherEnemyVector, Camera3 PlayerRef);

	void AI(double _dt, std::vector<Enemy> OtherEnemyRef);
	void DetectingPlayer();
	void Animation(double _dt);
	void PlayerPosUpdate(Camera3 NewPos);
	void Shoot();
	void BulletDecay();

	float ANIM_ROTATE = 0; //E01_Rotation
	float ENEMY_TURN = 0; //E01_RotationFace
	std::vector<Bullet> BulletContainer;

	float TimeToFire = 0;

private:
	bool DetectedPlayer = false;
	bool ANIMATION_MOVE = false;
	bool ReadyToFire = true;

	Camera3 PlayerRef;
};

#endif // !ENEMY_H

#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Camera3.h"


class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(Vector3 newPos, float EnemSizeX, float EnemSizeZ);
	~Enemy();
	void AiUpdate(double _dt, Camera3 NewPos);
	void bulletUpdate(double _dt, Camera3 NewPos);
	std::vector<Vector3> enemyVec;
	std::vector<Vector3> Bullets;
	bool targetCollide();

	void enemyVecLocation();
	void bulletLocation();
	
	/*void AI(double _dt);
	void DetectingPlayer();
	void Animation(double _dt);*/
	void PlayerPosUpdate(Camera3 NewPos);

	float ANIM_ROTATE[3]; //E01_Rotation
	float ENEMY_TURN[3]; //E01_RotationFace


private:
	bool DetectedPlayer = false;
	bool bulletInRange = false;
	

	Camera3 PlayerRef;

	Vector3 enemyCoords01 = Vector3(0, 0, 0);
	Vector3 enemyCoords02 = Vector3(100, 0, 100);
	Vector3 enemyCoords03 = Vector3(-100, 0, -100);
};

#endif // !ENEMY_H

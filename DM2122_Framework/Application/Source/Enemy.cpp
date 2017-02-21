#include "Enemy.h"

Enemy::Enemy()
{

}
Enemy::Enemy(Vector3 newPos, float EnemSizeX, float EnemSizeZ)
{
	setPosition(newPos);
	SizeX = EnemSizeX;
	SizeZ = EnemSizeZ;
}

Enemy::~Enemy()
{

}
void Enemy::PlayerPosUpdate(Camera3 NewPos)
{
	PlayerRef = NewPos;
}
void Enemy::enemyVecLocation()
{
	if (enemyVec.size() <= 0)
	{
		enemyVec.push_back(enemyCoords01);
		//EnemyHolder.push_back(MakeNewObject(enemyCoords01, 10, 10));
		enemyVec.push_back(enemyCoords02);
		//EnemyHolder.push_back(MakeNewObject(enemyCoords02, 10, 10));
		enemyVec.push_back(enemyCoords03);
		//EnemyHolder.push_back(MakeNewObject(enemyCoords03, 10, 10));
		Bullets.push_back(enemyCoords01);
		Bullets.push_back(enemyCoords02);
		Bullets.push_back(enemyCoords03);

	}
	else
	{
		enemyVec[0] = enemyCoords01;
		enemyVec[1] = enemyCoords02;
		enemyVec[2] = enemyCoords03;

		Bullets[0] = enemyCoords01;
		Bullets[1] = enemyCoords02;
		Bullets[2] = enemyCoords03;
	}

}
void Enemy::bulletLocation()
{
	if (Bullets.size() <= 0)
	{
		Bullets.push_back(enemyCoords01);
		Bullets.push_back(enemyCoords02);
		Bullets.push_back(enemyCoords03);
	}
	else
	{
		Bullets[0] = enemyCoords01;
		Bullets[1] = enemyCoords02;
		Bullets[2] = enemyCoords03;
	}
}
void Enemy::AiUpdate(double _dt, Camera3 NewPos)
{
	PlayerRef = NewPos;

	static float ENEMY_TURN_LIMIT = 1;
	static float ANIM_ROTATE_LIMIT = 1;
	

	for (int i = 0; i < enemyVec.size(); i++)
	{
		int RESET_TO_ZERO = 0;
		Vector3 distance = (PlayerRef.target - enemyVec[i]);

		if ((enemyVec[i] - PlayerRef.target).Length() <= 200)
		{
			DetectedPlayer = true;
			bulletInRange = true;
		}
		else
		{
			DetectedPlayer = false;
			bulletInRange = false;
		}

		if (distance.Length() > 200 && DetectedPlayer == false)
		{
			//Animation Reset
			RESET_TO_ZERO = 0 - ANIM_ROTATE[i];
			ANIM_ROTATE[i] += (float)(5 * _dt * RESET_TO_ZERO);
		}
		if (DetectedPlayer == true)
		{
			ENEMY_TURN[i] = Math::RadianToDegree(atan2(distance.x, distance.z));
			for (int j = 0; j < enemyVec.size(); j++)
			{
				if (i != j)
				{
					if (((enemyVec[i] + distance *_dt) - enemyVec[j]).Length() >= 70)
					{
						if (distance.Length() <= 200 && distance.Length() >= 100)
						{
							//Movement
							enemyVec[i] += distance * _dt * 0.2f;
						}
						if (distance.Length() >= 100)
						{
							//Animate Legs
							ANIM_ROTATE[i] += (float)(100 * _dt * ANIM_ROTATE_LIMIT);
						}

						else
						{
							RESET_TO_ZERO = 0 - ANIM_ROTATE[i];
							ANIM_ROTATE[i] += (float)(5 * _dt * RESET_TO_ZERO);
						}

						//Looping
						if (ANIM_ROTATE[i] < -40 || ANIM_ROTATE[i] > 40)
						{
							ANIM_ROTATE_LIMIT *= -1;
						}
					}
					else
					{
						bulletInRange = true;
						RESET_TO_ZERO = 0 - ANIM_ROTATE[i];
						ANIM_ROTATE[i] += (float)(100 * _dt * RESET_TO_ZERO);
						enemyVec[i] -= distance * _dt * 0.4;
						//enemyVec[i] = enemyVec[i];
						//std::cout << "break" << std::endl;
						break;
						
					}
				}
				/*else
				{
					enemyVec[i] = enemyVec[i];
				}*/

			}
			
		}
	}
	
}
void Enemy::bulletUpdate(double _dt, Camera3 newPos)
{
	PlayerRef = newPos;
	for (int x = 0; x < Bullets.size(); x++)
	{
		///bullet update
		if (bulletInRange == true)
		{
			Vector3 bulletDistance = (PlayerRef.target - Bullets[x]);
			Bullets[x] += bulletDistance * _dt * 0.5;
		}
	}
}
bool Enemy::targetCollide()
{
	for (int i = 0; i < Bullets.size(); i++)
	{
		Vector3 bulletDist = (Bullets[i] - PlayerRef.target);
		if (bulletDist == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
//void Enemy::AI(double _dt)
//{
//	static float ENEMY_TURN_LIMIT = 1;
//
//	Vector3 distance = PlayerRef.target - this->position_;
//
//	if (DetectedPlayer == true)
//	{
//		ENEMY_TURN = Math::RadianToDegree(atan2(distance.x, distance.z));
//		if ((this->position_ - PlayerRef.target).Length() <= 200 && (this->position_ - PlayerRef.target).Length() >= 100)
//		{
//			//Movement
//			this->position_ += distance * _dt * 0.2f;
//		}
//	}
//	else
//	{
//		this->setPosition(this->position_);
//	}
//}
//
//void Enemy::DetectingPlayer()
//{
//	if ((this->position_ - PlayerRef.target).Length() <= 200)
//	{
//		DetectedPlayer = true;
//	}
//	else
//	{
//		DetectedPlayer = false;
//	}
//}
//
//void Enemy::Animation(double _dt)
//{
//	static float ANIM_ROTATE_LIMIT = 1;
//	int RESET_TO_ZERO = 0;
//
//	if (DetectedPlayer == true)
//	{
//		if ((this->position_ - PlayerRef.target).Length() >= 100)
//		{
//			//Animate Legs
//			ANIM_ROTATE += (float)(100 * _dt * ANIM_ROTATE_LIMIT);
//		}
//		else
//		{
//			//Animation Reset
//			RESET_TO_ZERO = 0 - ANIM_ROTATE;
//			ANIM_ROTATE += (float)(5 * _dt * RESET_TO_ZERO);
//		}
//
//		//Looping
//		if (ANIM_ROTATE < -40 || ANIM_ROTATE > 40)
//		{
//			ANIM_ROTATE_LIMIT *= -1;
//		}
//	}
//	else
//	{
//		RESET_TO_ZERO = 0 - ANIM_ROTATE;
//		ANIM_ROTATE += (float)(5 * _dt * RESET_TO_ZERO);
//	}
//}
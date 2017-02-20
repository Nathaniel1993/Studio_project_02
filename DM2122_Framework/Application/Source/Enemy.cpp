#include "Enemy.h"

Enemy::Enemy(Vector3 newPos, int EnemSizeX, int EnemSizeZ)
{
	setPosition(newPos);
	SizeX = EnemSizeX;
	SizeZ = EnemSizeZ;
}

Enemy::~Enemy()
{

}

void Enemy::AI(double _dt)
{
	static float ENEMY_TURN_LIMIT = 1;

	Vector3 distance = PlayerRef.target - this->position_;

	if (DetectedPlayer == true)
	{
		ENEMY_TURN = Math::RadianToDegree(atan2(distance.x, distance.z));
		if ((this->position_ - PlayerRef.target).Length() <= 200 && (this->position_ - PlayerRef.target).Length() >= 100)
		{
			//Movement
			this->position_ += distance * _dt * 0.2f;
		}
	}
	else
	{
		this->setPosition(this->position_);
	}
}

void Enemy::DetectingPlayer()
{
	if ((this->position_ - PlayerRef.target).Length() <= 200)
	{
		DetectedPlayer = true;
	}
	else
	{
		DetectedPlayer = false;
	}
}

void Enemy::Animation(double _dt)
{
	static float ANIM_ROTATE_LIMIT = 1;
	int RESET_TO_ZERO = 0;

	if (DetectedPlayer == true)
	{
		if ((this->position_ - PlayerRef.target).Length() >= 100)
		{
			//Animate Legs
			ANIM_ROTATE += (float)(100 * _dt * ANIM_ROTATE_LIMIT);
		}
		else
		{
			//Animation Reset
			RESET_TO_ZERO = 0 - ANIM_ROTATE;
			ANIM_ROTATE += (float)(5 * _dt * RESET_TO_ZERO);
		}

		//Looping
		if (ANIM_ROTATE < -40 || ANIM_ROTATE > 40)
		{
			ANIM_ROTATE_LIMIT *= -1;
		}
	}
	else
	{
		RESET_TO_ZERO = 0 - ANIM_ROTATE;
		ANIM_ROTATE += (float)(5 * _dt * RESET_TO_ZERO);
	}
}

void Enemy::PlayerPosUpdate(Camera3 NewPos)
{
	PlayerRef = NewPos;
}
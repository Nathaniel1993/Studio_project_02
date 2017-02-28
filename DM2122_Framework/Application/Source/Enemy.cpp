#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(Vector3 newPos, float EnemSizeX, float EnemSizeZ, EnemyType ThisType)
{
	setPosition(newPos);
	SizeX = EnemSizeX;
	SizeZ = EnemSizeZ;
	TypeOfEnemy = ThisType;
}

Enemy::~Enemy()
{

}

EnemyType Enemy::GetEnemyType()
{
	return TypeOfEnemy;
}

void Enemy::Update(double TimeIntake, std::vector<Enemy> OtherEnemyVector, Player PlayerRef)
{
	this->PlayerPosUpdate(PlayerRef);
	this->DetectingPlayer();
	this->AI(TimeIntake, OtherEnemyVector);
	this->Animation(TimeIntake);
	if (TypeOfEnemy == Ranged && BulletContainer.size() > 0)
	{
		this->BulletDecay();
	}
}

void Enemy::PlayerPosUpdate(Player NewPos)
{
	PlayerRef = NewPos;
}

void Enemy::AI(double _dt, std::vector<Enemy> OtherEnemyRef)
{
	TimeToFire += _dt;

	static float ENEMY_TURN_LIMIT = 1;

	Vector3 distance = PlayerRef.getPosition() - this->position_;

	if (DetectedPlayer == true)
	{
		ENEMY_TURN = Math::RadianToDegree(atan2(distance.x, distance.z));

		if (fmod(TimeToFire, 2.0f) < 0.05f)
		{
			ReadyToFire = true;
		}

		for (int i = 0; i < OtherEnemyRef.size(); i++)
		{
			if (OtherEnemyRef[i].getPosition() != this->getPosition()) //Checks if THIS Enemy's Position is not the reference position
			{
				if (((this->getPosition() + distance * _dt) - OtherEnemyRef[i].getPosition()).Length() >= 50)
				{
					if (i == (OtherEnemyRef.size() - 1))
					{
						if (TypeOfEnemy == Ranged)
						{
							if ((this->position_ - PlayerRef.getPosition()).Length() <= 200 && (this->position_ - PlayerRef.getPosition()).Length() >= 100) //player detetcted
							{
								float nextXPos = this->getPosition().x + distance.x * _dt * 0.3f;
								float nextZPos = this->getPosition().z + distance.z * _dt * 0.3f;

								for (int j = 0; j < AllSceneStaticObjects.size(); j++)
								{
									if (nextXPos <= AllSceneStaticObjects[j].getPosition().x + AllSceneStaticObjects[j].getSizeX()
										&& nextXPos >= AllSceneStaticObjects[j].getPosition().x - AllSceneStaticObjects[j].getSizeX())
									{
										if (nextZPos <= AllSceneStaticObjects[j].getPosition().z + AllSceneStaticObjects[j].getSizeZ()
											&& nextZPos >= AllSceneStaticObjects[j].getPosition().z - AllSceneStaticObjects[j].getSizeZ())
										{
											this->position_ -= distance * _dt * 0.3f;
										}
									}
								}
								this->position_ += distance * _dt * 0.3f;
								ANIMATION_MOVE = true;
							}
							else
							{
								if (ReadyToFire == true)
								{
									Shoot();
									ReadyToFire = false;
								}
								ANIMATION_MOVE = false;
							}
						}
						else
						{
							if ((this->position_ - PlayerRef.getPosition()).Length() <= 200 && (this->position_ - PlayerRef.getPosition()).Length() >= 30)
							{
								this->position_ += distance * _dt * 0.3f;
								ANIMATION_MOVE = true;
							}
							else
							{
								ANIMATION_MOVE = false;
							}
						}
					}
				}
				else
				{
					ANIMATION_MOVE = false;
					break;
				}
			}
		}
	}
	else
	{
		this->setPosition(this->position_);
	}
}

void Enemy::DetectingPlayer()
{
	if (PlayerRef.isInvisible == true)
	{
		DetectedPlayer = false;
	}
	else
	{
		if ((this->position_ - PlayerRef.getPosition()).Length() <= 200)
		{
			DetectedPlayer = true;
		}
		else
		{
			DetectedPlayer = false;
		}
	}
}

void Enemy::Animation(double _dt)
{
	static float ANIM_ROTATE_LIMIT = 1;
	int RESET_TO_ZERO = 0;

	if (ANIMATION_MOVE == true)
	{
		ANIM_ROTATE += (float)(100 * _dt * ANIM_ROTATE_LIMIT);
		if (ANIM_ROTATE < -40 || ANIM_ROTATE > 40)
		{
			ANIM_ROTATE_LIMIT *= -1;
		}
	}
	else
	{
		//Animation Reset
		RESET_TO_ZERO = 0 - ANIM_ROTATE;
		ANIM_ROTATE += (float)(5 * _dt * RESET_TO_ZERO);
	}
}

void Enemy::Shoot()
{
	Bullet newBullet(this->getPosition(), PlayerRef);

	BulletContainer.push_back(newBullet);
}

void Enemy::BulletDecay()
{
	for (int i = 0; i < BulletContainer.size(); i++)
	{
		if (BulletContainer[i].TimeToDecay >= 3.0f || BulletContainer[i].playerHit == true)
		{
			BulletContainer.erase(BulletContainer.begin() + i);
			break;
		}
		else
		{
			BulletContainer[i].playerHit = false;
		}
		for (int j = 0; j < AllSceneStaticObjects.size(); j++)
		{
			if (BulletContainer[i].getPosition().x + BulletContainer[i].getSizeX() <= AllSceneStaticObjects[j].getPosition().x + AllSceneStaticObjects[j].getSizeX()
				&& BulletContainer[i].getPosition().x + BulletContainer[i].getSizeX() >= AllSceneStaticObjects[j].getPosition().x - AllSceneStaticObjects[j].getSizeX())
			{
				if (BulletContainer[i].getPosition().z + BulletContainer[i].getSizeZ() <= AllSceneStaticObjects[j].getPosition().z + AllSceneStaticObjects[j].getSizeZ()
					&& BulletContainer[i].getPosition().z + BulletContainer[i].getSizeZ() >= AllSceneStaticObjects[j].getPosition().z - AllSceneStaticObjects[j].getSizeZ())
				{
					BulletContainer.erase(BulletContainer.begin() + i);
					break;
				}
			}
		}
	}
}
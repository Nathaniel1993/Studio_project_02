#include "GameObject.h"

GameObject::GameObject()
{
	position_ = Vector3(1, 0, 0);
	SizeX = 1;
	SizeZ = 1;
}

GameObject::GameObject(Vector3 newposition)
{
	position_ = newposition;
	SizeX = 1;
	SizeZ = 1;
}

GameObject::GameObject(Vector3 newposition, int newsizeX, int newSizeZ)
{
	position_ = newposition;
	SizeX = newsizeX;
	SizeZ = newSizeZ;
}

GameObject::~GameObject()
{

}

Vector3 GameObject::getPosition()
{
	return position_;
}

void GameObject::setPosition(Vector3 newPos)
{
	position_ = newPos;
}

int GameObject::getSizeX()
{
	return SizeX;
}

int GameObject::getSizeZ()
{
	return SizeZ;
}

//void GameObject::enemyVecLocation()
//{
//	if (enemyVec.size() <= 0)
//	{
//		enemyVec.push_back(enemyCoords01);
//		//EnemyHolder.push_back(MakeNewObject(enemyCoords01, 10, 10));
//		enemyVec.push_back(enemyCoords02);
//		//EnemyHolder.push_back(MakeNewObject(enemyCoords02, 10, 10));
//		enemyVec.push_back(enemyCoords03);
//		//EnemyHolder.push_back(MakeNewObject(enemyCoords03, 10, 10));
//	}
//	else
//	{
//		enemyVec[0] = enemyCoords01;
//		enemyVec[1] = enemyCoords02;
//		enemyVec[2] = enemyCoords03;
//	}
//}
//
//void GameObject::EnemyBrain(double _dt)
//{
//	static float E01_RotaLimit = 1;
//	static float E01_RotationFaceLimit = 1;
//	bool detectPlayer = false;
//
//	for (int i = 0; i < 3; i++)
//	{
//
//		int resetE01_rota = 0;
//		Vector3 distance = (cameraP.target - enemyVec[i]);
//		//Player Detection
//		if ((enemyVec[i] - cameraP.target).Length() <= 200) //&& (enemyVec[i] - cameraP.target).Length() >= 100)
//		{
//			detectPlayer = true;
//			std::cout << "detected" << std::endl;
//		}
//		else
//		{
//			detectPlayer = false;
//		}
//
//		if (((enemyVec[i] - cameraP.target).Length() > 200 && detectPlayer == false))
//		{
//			resetE01_rota = 0 - E01_Rotation[i];
//			E01_Rotation[i] += (float)(5 * _dt* resetE01_rota);
//		}
//
//		//Enemy AI
//		if (detectPlayer == true)
//		{
//			E01_RotationFace[i] = Math::RadianToDegree(atan2(distance.x, distance.z));
//			for (int j = 0; j < 3; j++)
//			{
//				if (i != j)
//				{
//					if (((enemyVec[i] + distance *_dt) - enemyVec[j]).Length() >= 70)
//					{
//						//if ((enemyVec[i] - cameraP.target).Length() >= 50)
//						//{
//						if ((enemyVec[i] - cameraP.target).Length() <= 200 && (enemyVec[i] - cameraP.target).Length() >= 100)
//						{
//							//Movement
//							enemyVec[i] += distance * _dt * 0.2;
//						}
//
//						if ((enemyVec[i] - cameraP.target).Length() >= 100)
//						{
//							//Animate Legs
//							E01_Rotation[i] += (float)(100 * _dt * E01_RotaLimit);
//						}
//						else
//						{
//							//Animation Reset
//							resetE01_rota = 0 - E01_Rotation[i];
//							E01_Rotation[i] += (float)(5 * _dt* resetE01_rota);
//							//ReadyToFire = true;
//						}
//
//						// Leg Rotation Limit
//						if (E01_Rotation[i] < -40 || E01_Rotation[i] > 40)
//						{
//							E01_RotaLimit *= -1;
//						}
//						//}
//						//else
//						//{
//						//	resetE01_rota = 0 - E01_Rotation[i];
//						//	E01_Rotation[i] += (float)(5 * _dt* resetE01_rota);
//						//	enemyVec[i] = enemyVec[i];
//						//}
//					}
//					else //if ((enemyVec[i] - enemyVec[j]).Length() <= 10)
//					{
//						resetE01_rota = 0 - E01_Rotation[i];
//						E01_Rotation[i] += (float)(100 * _dt* resetE01_rota);
//						enemyVec[i] = enemyVec[i];
//						break;
//					}
//				}
//				else
//				{
//					enemyVec[i] = enemyVec[i];
//				}
//			}
//
//		}
//
//	}
//}
//void GameObject::CollisionCheck()
//{
//	for (int i = 0; i < EnemyHolder.size(); i++)
//	{
//		if (cameraP.target.x - (EnemyHolder[i].getPosition().x - EnemyHolder[i].getSizeX()) <= (4 + EnemyHolder[i].getSizeX())
//			&& cameraP.target.x - (EnemyHolder[i].getPosition().x - EnemyHolder[i].getSizeX()) > 0)
//		{
//			if (cameraP.target.z - (EnemyHolder[i].getPosition().z - EnemyHolder[i].getSizeZ()) <= (4 + EnemyHolder[i].getSizeZ())
//				&& cameraP.target.z - (EnemyHolder[i].getPosition().z - EnemyHolder[i].getSizeZ()) > 0)
//			{
//				std::cout << "Collided at X: " << cameraP.target.x << " and Z : " << cameraP.target.z << std::endl;
//			}
//		}
//	}
//}
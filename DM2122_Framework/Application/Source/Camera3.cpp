#include "Camera3.h"
#include "Mtx44.h"
#include"Application.h"
#include <iostream>
#include <GLFW/glfw3.h>

POINT delta, check, Pos;
using std::cout;
using std::endl;

//DO NOT REMOVE
std::vector<GameObject> AllSceneStaticObjects;
std::vector<GameObject> Scene02DoorContainer;
std::vector<GameObject> Scene03LeftDoorContainer;
std::vector<GameObject> Scene03RightDoorContainer;
std::vector<GameObject> CrateContainer;

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera3::Camera3()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera3::~Camera3()
{
}

/******************************************************************************/
/*!
\brief
Initialize Camera3

\param pos - position of Camera3
\param target - where the Camera3 is looking at
\param up - up vector of Camera3
*/
/******************************************************************************/
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	tempPos = Vector3(0, 50, 0) - view * 300;
}

/******************************************************************************/
/*!
\brief
Reset the Camera3 settings
*/
/******************************************************************************/
void Camera3::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera3 will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera3::Update(double dt, float *rotateAngle)
{
	static float ArmRotateLimit = 1;
	static float ArmRotateReset = 1;
	static float LegRotateLimit = 1;
	static float LegRotateReset = 1;

	static float SwingRotateLimit = 1;
	static float SwingRotateReset = 1;

	static float wristRotateLimit = 1;
	static float wristRotateReset = 1;

	view = (target - position).Normalized();
	right = view.Cross(up);//cross product
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();

	float run = 3.0f;

	Mtx44 rotation;

	if (Application::IsKeyPressed(VK_SPACE))
	{
		run = 10.0f;
	}
	position = tempPos + target;
	//=============movement====================================
	if (Application::IsKeyPressed('A'))
	{
		//position -= right * (float)(50.f * run * dt);
		//target -= right * (float)(50.f * run * dt);
		rotateBody += (float)(100 * dt);
	}

	if (Application::IsKeyPressed('D'))
	{
		//position += right * (float)(50.f * run * dt);
		//target += right * (float)(50.f * run * dt);
		rotateBody -= (float)(100 * dt);
	}

	if (Application::IsKeyPressed('W'))
	{
		position.x += (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
		target.x += (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
		position.z += (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
		target.z += (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);

		//Collision
		for (unsigned int i = 0; i < AllSceneStaticObjects.size(); i++)
		{
			if (target.x >= AllSceneStaticObjects[i].getPosition().x - AllSceneStaticObjects[i].getSizeX()
				&& AllSceneStaticObjects[i].getPosition().x + AllSceneStaticObjects[i].getSizeX() >= target.x)
			{
				if (target.z >= AllSceneStaticObjects[i].getPosition().z - AllSceneStaticObjects[i].getSizeZ()
					&& AllSceneStaticObjects[i].getPosition().z + AllSceneStaticObjects[i].getSizeZ() >= target.z)
				{
					position.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					target.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					position.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
					target.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
				}
			}
		}

		//Scene 2 Door Collision
		for (unsigned int i = 0; i < Scene02DoorContainer.size(); i++)
		{
			if (target.x >= Scene02DoorContainer[i].getPosition().x - Scene02DoorContainer[i].getSizeX()
				&& Scene02DoorContainer[i].getPosition().x + Scene02DoorContainer[i].getSizeX() >= target.x)
			{
				if (target.z >= Scene02DoorContainer[i].getPosition().z - Scene02DoorContainer[i].getSizeZ()
					&& Scene02DoorContainer[i].getPosition().z + Scene02DoorContainer[i].getSizeZ() >= target.z)
				{
					position.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					target.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					position.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
					target.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
				}
			}
		}

		//Scene 3 Door Collision
		for (int i = 0; i < Scene03LeftDoorContainer.size(); i++)
		{
			if (target.x >= Scene03LeftDoorContainer[i].getPosition().x - Scene03LeftDoorContainer[i].getSizeX()
				&& Scene03LeftDoorContainer[i].getPosition().x + Scene03LeftDoorContainer[i].getSizeX() >= target.x)
			{
				if (target.z >= Scene03LeftDoorContainer[i].getPosition().z - Scene03LeftDoorContainer[i].getSizeZ()
					&& Scene03LeftDoorContainer[i].getPosition().z + Scene03LeftDoorContainer[i].getSizeZ() >= target.z)
				{
					position.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					target.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					position.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
					target.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
				}
			}
		}

		//Scene 3 Door Collision
		for (unsigned int i = 0; i < Scene03RightDoorContainer.size(); i++)
		{
			if (target.x >= Scene03RightDoorContainer[i].getPosition().x - Scene03RightDoorContainer[i].getSizeX()
				&& Scene03RightDoorContainer[i].getPosition().x + Scene03RightDoorContainer[i].getSizeX() >= target.x)
			{
				if (target.z >= Scene03RightDoorContainer[i].getPosition().z - Scene03RightDoorContainer[i].getSizeZ()
					&& Scene03RightDoorContainer[i].getPosition().z + Scene03RightDoorContainer[i].getSizeZ() >= target.z)
				{
					position.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					target.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					position.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
					target.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
				}
			}
		}

		//Crate Collision
		for (unsigned int i = 0; i < CrateContainer.size(); i++)
		{
			if (target.x >= CrateContainer[i].getPosition().x - CrateContainer[i].getSizeX()
				&& CrateContainer[i].getPosition().x + CrateContainer[i].getSizeX() >= target.x)
			{
				if (target.z >= CrateContainer[i].getPosition().z - CrateContainer[i].getSizeZ()
					&& CrateContainer[i].getPosition().z + CrateContainer[i].getSizeZ() >= target.z)
				{
					position.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					target.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					position.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
					target.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
				}
			}
		}

		//Animation
		rotateArms += (float)(80 * ArmRotateLimit * dt);
		rotateLegs += (float)(80 * LegRotateLimit * dt);
		if (rotateArms > 20 || rotateArms < -20)
		{
			ArmRotateLimit *= -1;
		}
		if (rotateLegs > 10 || rotateLegs < -10)
		{
			LegRotateLimit *= -1;
		}
	}

	if (Application::IsKeyPressed('S'))
	{
		position.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
		target.x -= (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
		position.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
		target.z -= (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);

		//Collision
		for (unsigned int i = 0; i < AllSceneStaticObjects.size(); i++)
		{
			if (target.x >= AllSceneStaticObjects[i].getPosition().x - AllSceneStaticObjects[i].getSizeX()
				&& AllSceneStaticObjects[i].getPosition().x + AllSceneStaticObjects[i].getSizeX() >= target.x)
			{
				if (target.z >= AllSceneStaticObjects[i].getPosition().z - AllSceneStaticObjects[i].getSizeZ()
					&& AllSceneStaticObjects[i].getPosition().z + AllSceneStaticObjects[i].getSizeZ() >= target.z)
				{
					position.x += (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					target.x += (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					position.z += (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
					target.z += (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
				}
			}
		}

		//Scene 02 Door Collision
		for (unsigned int i = 0; i < Scene02DoorContainer.size(); i++)
		{
			if (target.x >= Scene02DoorContainer[i].getPosition().x - Scene02DoorContainer[i].getSizeX()
				&& Scene02DoorContainer[i].getPosition().x + Scene02DoorContainer[i].getSizeX() >= target.x)
			{
				if (target.z >= Scene02DoorContainer[i].getPosition().z - Scene02DoorContainer[i].getSizeZ()
					&& Scene02DoorContainer[i].getPosition().z + Scene02DoorContainer[i].getSizeZ() >= target.z)
				{
					position.x += (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					target.x += (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					position.z += (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
					target.z += (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
				}
			}
		}

		//Scene 03 Door Collision
		for (unsigned int i = 0; i < Scene03LeftDoorContainer.size(); i++)
		{
			if (target.x >= Scene03LeftDoorContainer[i].getPosition().x - Scene03LeftDoorContainer[i].getSizeX()
				&& Scene03LeftDoorContainer[i].getPosition().x + Scene03LeftDoorContainer[i].getSizeX() >= target.x)
			{
				if (target.z >= Scene03LeftDoorContainer[i].getPosition().z - Scene03LeftDoorContainer[i].getSizeZ()
					&& Scene03LeftDoorContainer[i].getPosition().z + Scene03LeftDoorContainer[i].getSizeZ() >= target.z)
				{
					position.x += (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					target.x += (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					position.z += (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
					target.z += (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
				}
			}
		}

		//Scene 03 Door Collision
		for (unsigned int i = 0; i < Scene03RightDoorContainer.size(); i++)
		{
			if (target.x >= Scene03RightDoorContainer[i].getPosition().x - Scene03RightDoorContainer[i].getSizeX()
				&& Scene03RightDoorContainer[i].getPosition().x + Scene03RightDoorContainer[i].getSizeX() >= target.x)
			{
				if (target.z >= Scene03RightDoorContainer[i].getPosition().z - Scene03RightDoorContainer[i].getSizeZ()
					&& Scene03RightDoorContainer[i].getPosition().z + Scene03RightDoorContainer[i].getSizeZ() >= target.z)
				{
					position.x += (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					target.x += (float)(50.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
					position.z += (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
					target.z += (float)(50.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
				}
			}
		}

		//Animation
		rotateArms -= (float)(60 * ArmRotateLimit * dt);
		rotateLegs -= (float)(60 * LegRotateLimit * dt);
		if (rotateArms > 20 || rotateArms < -20)
		{
			ArmRotateLimit *= -1;
		}
		if (rotateLegs > 10 || rotateLegs < -10)
		{
			LegRotateLimit *= -1;
		}
	}
	if (!Application::IsKeyPressed('W') && !Application::IsKeyPressed('S'))
	{
		ArmRotateReset = 0 - rotateArms;
		rotateArms += (float)(10 * ArmRotateReset * dt);
		LegRotateReset = 0 - rotateLegs;
		rotateLegs += (float)(10 * LegRotateReset * dt);
	}
	//====================camera - keyboard=========================
	if (Application::IsKeyPressed('E') || Application::IsKeyPressed('A')) //Look left
	{
		float rotateView = (float)(100 * dt);
		rotation.SetToRotation(rotateView, 0, 1, 0);
		tempPos = rotation * tempPos;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('Q') || Application::IsKeyPressed('D')) //Look right
	{
		float rotateView = (float)(100 * dt);
		rotation.SetToRotation(-rotateView, 0, 1, 0);
		tempPos = rotation * tempPos;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('R')) //Look up
	{
		float rotateView = (float)(100 * dt);
		rotation.SetToRotation(-rotateView, right.x, right.y, right.z);
		tempPos = rotation * tempPos;
	}
	if (Application::IsKeyPressed('F')) //Look down
	{
		float rotateView = (float)(100 * dt);
		rotation.SetToRotation(rotateView, right.x, right.y, right.z);
		tempPos = rotation * tempPos;
	}
	//============================ COMBAT ==================================
	if (Application::IsKeyPressed(MK_LBUTTON) && hit == false)
	{
		rotateArmR += (float)(200 * SwingRotateLimit * dt);
		if (rotateArmR > 1 || rotateArmR < -100)
		{
			SwingRotateLimit *= -1;
			hit = true;

		}
		rotateHandR += (float)(500 * wristRotateLimit * dt);
		if (rotateHandR > 1 || rotateHandR < -90)
		{
			wristRotateLimit *= -1;
			//hit = true;
		}
	}
	else if (!Application::IsKeyPressed(MK_LBUTTON) || hit == true)
	{
		wristRotateReset = 0 - rotateHandR;
		rotateHandR += (float)(50 * wristRotateReset * dt);
		SwingRotateReset = 0 - rotateArmR;
		rotateArmR += (float)(50 * SwingRotateReset * dt);
		hit = false;
	}
	if (Application::IsKeyPressed(MK_RBUTTON))
	{
		rotateArmL -= (float)(400 * dt);

		if (rotateArmL <= -90)
		{
			rotateArmL = -90;
		}
	}
	else if (!Application::IsKeyPressed(MK_RBUTTON))
	{

		SwingRotateReset = 0 - rotateArmL;
		rotateArmL += (float)(50 * SwingRotateReset * dt);
	}
}


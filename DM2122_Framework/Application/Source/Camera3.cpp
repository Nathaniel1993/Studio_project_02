#include "Camera3.h"
#include "Mtx44.h"
#include"Application.h"
#include <iostream>
#include <GLFW/glfw3.h>
POINT delta, check, Pos;
using std::cout;
using std::endl;

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
	view = (target - position).Normalized();
	right = view.Cross(up);//cross product
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();

	float run = 10.0f;

	Mtx44 rotation;

	if (Application::IsKeyPressed(VK_SPACE))
	{
		run = 20.0f;
	}
	position = tempPos + target;
	//=============movement====================================
	if (Application::IsKeyPressed('A'))
	{
		target -= right * (float)(50.f * run * dt);
	}
	if (Application::IsKeyPressed('D'))
	{
		target += right * (float)(50.f * run * dt);
	}
	if (Application::IsKeyPressed('W'))
	{
		target.x += view.x * (float)(50.f * run * dt);
		target.z += view.z * (float)(50.f * run * dt);
	}
	if (Application::IsKeyPressed('S'))
	{
		target.x -= view.x * (float)(50.f * run * dt);
		target.z -= view.z * (float)(50.f * run * dt);
	}
	//====================camera - keyboard=========================
	if (Application::IsKeyPressed(VK_LEFT)) //Look left
	{
		float rotateView = (float)(70 * dt);
		rotation.SetToRotation(rotateView, 0, 1, 0);
		tempPos = rotation * tempPos;
		up = rotation * up;
	}
	if (Application::IsKeyPressed(VK_RIGHT)) //Look right
	{
		float rotateView = (float)(70 * dt);
		rotation.SetToRotation(-rotateView, 0, 1, 0);
		tempPos = rotation * tempPos;
		up = rotation * up;
	}
	if (Application::IsKeyPressed(VK_UP)) //Look up
	{
		float rotateView = (float)(50 * dt);
		if (*rotateAngle >= -15)
		{
			rotation.SetToRotation(-rotateView, right.x, right.y, right.z);
			tempPos = rotation * tempPos;
			*rotateAngle -= 1;
		}
	}
	if (Application::IsKeyPressed(VK_DOWN)) //Look down
	{
		float rotateView = (float)(50 * dt);
		if (*rotateAngle <= 5)
		{
			rotation.SetToRotation(rotateView, right.x, right.y, right.z);
			tempPos = rotation * tempPos;
			*rotateAngle += 1;
		}
	}
	//==============================================================
}


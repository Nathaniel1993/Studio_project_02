#include "Camera3.h"
#include "Mtx44.h"
#include"Application.h"

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

	view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();

	float run = 3.0f;

	Mtx44 rotation;

	if (Application::IsKeyPressed(VK_SPACE)) //increase movement speed while held down
	{
		run = 10.0f;
	}
	position = tempPos + target; //moves camera along with character
	//=============movement====================================
	if (Application::IsKeyPressed('A')) //turn left
	{
		rotateBody += (float)(100 * dt);
	}

	if (Application::IsKeyPressed('D')) //turn right
	{
		rotateBody -= (float)(100 * dt);
	}

	if (Application::IsKeyPressed('W')) //walk forward
	{
		position.x += view.x * (float)(100.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
		position.z += view.z * (float)(100.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
		target.x += view.x *(float)(100.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
		target.z += view.z * (float)(100.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
		rotateArms -= (float)(80 * ArmRotateLimit * dt);
		rotateLegs -= (float)(80 * LegRotateLimit * dt);
		if (rotateArms > 20 || rotateArms < -20)
		{
			ArmRotateLimit *= -1;
		}
		if (rotateLegs > 10 || rotateLegs < -10)
		{
			LegRotateLimit *= -1;
		}
	}

	if (Application::IsKeyPressed('S')) //walk backward
	{
		position.x -= view.x * (float)(100.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
		position.z -= view.z * (float)(100.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
		target.x -= view.x * (float)(100.f * run * sin(Math::DegreeToRadian(rotateBody)) * dt);
		target.z -= view.z * (float)(100.f * run * cos(Math::DegreeToRadian(rotateBody)) * dt);
		rotateArms += (float)(60 * ArmRotateLimit * dt);
		rotateLegs += (float)(60 * LegRotateLimit * dt);
		if (rotateArms > 20 || rotateArms < -20)
		{
			ArmRotateLimit *= -1;
		}
		if (rotateLegs > 10 || rotateLegs < -10)
		{
			LegRotateLimit *= -1;
		}
	}
	//reset positions of arms & legs
	if (!Application::IsKeyPressed('W') && !Application::IsKeyPressed('S'))
	{

		ArmRotateReset = 0 - rotateArms;
		rotateArms += (float)(10 * ArmRotateReset * dt);
		LegRotateReset = 0 - rotateLegs;
		rotateLegs += (float)(10 * LegRotateReset * dt);
	}
	//====================camera - keyboard=========================
	if (Application::IsKeyPressed(VK_LEFT)) //Look left
	{
		float rotateView = (float)(70 * dt);
		if (yawLimit >= -15)
		{
			rotation.SetToRotation(rotateView, 0, 1, 0);
			tempPos = rotation * tempPos;
			up = rotation * up;
			yawLimit -= 1;
		}
	}
	if (Application::IsKeyPressed(VK_RIGHT)) //Look right
	{
		float rotateView = (float)(70 * dt);
		if (yawLimit <= 15)
		{
			rotation.SetToRotation(-rotateView, 0, 1, 0);
			tempPos = rotation * tempPos;
			up = rotation * up;
			yawLimit += 1;
		}
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


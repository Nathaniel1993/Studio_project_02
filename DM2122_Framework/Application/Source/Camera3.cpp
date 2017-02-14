#include "Camera3.h"
#include "Mtx44.h"
#include"Application.h"
#include <iostream>
#include <GLFW/glfw3.h>
extern GLFWwindow* m_window;
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
	this->position = pos;
	this->target = target;
	this->up = up;

	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	xpos = 0;
	ypos = 0;

	right.y = 0;
	right.Normalize();
	this->up = right.Cross(view).Normalized();

	view = target - position;
	right = view.Cross(up).Normalized();

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

	float run = 5.0f;

	//Mtx44 rotation, yaw, pitch;
	//yaw = mouseY;
	//pitch = mouseX;
	//Mtx44 camPitch, camYaw;

	////get cursor position
	//glfwGetCursorPos(m_window, &xpos, &ypos);

	//int mid_x = 800 / 2;
	//int mid_y = 600 / 2;

	//glfwSetCursorPos(m_window, mid_x, mid_y);

	////mouse speed
	//horizMovement = Math::DegreeToRadian((mid_x - xpos) * 3);
	//vertMovement = Math::DegreeToRadian((mid_y - ypos) * 3);

	//// control vertical limit
	//verticalAngle += dt *Math::RadianToDegree(vertMovement);
	//if (verticalAngle > 78)
	//{
	//	verticalAngle = 78;
	//	vertMovement = 0;
	//}
	//else if (verticalAngle < -75)
	//{
	//	verticalAngle = -75;
	//	vertMovement = 0;
	//}

	//up = right.Cross(view).Normalized();

	//view = target - position;
	//right = view.Cross(up).Normalized();
	if (Application::IsKeyPressed(VK_SPACE))
	{
		run = 10.0f;
	}
	if (Application::IsKeyPressed('A'))
	{
		position -= right * (float)(50.f * run * dt);
		target -= right * (float)(50.f * run * dt);
	}
	if (Application::IsKeyPressed('D'))
	{
		position += right * (float)(50.f * run * dt);
		target += right * (float)(50.f * run * dt);
	}
	if (Application::IsKeyPressed('W'))
	{
		position.x += view.x * (float)(50.f * run * dt);
		position.z += view.z * (float)(50.f * run * dt);
		target.x += view.x * (float)(50.f * run * dt);
		target.z += view.z * (float)(50.f * run * dt);
	}
	if (Application::IsKeyPressed('S'))
	{
		position.x -= view.x * (float)(50.f * run * dt);
		position.z -= view.z * (float)(50.f * run * dt);
		target.x -= view.x * (float)(50.f * run * dt);
		target.z -= view.z * (float)(50.f * run * dt);
	}

	//camPitch.SetToIdentity();
	//camYaw.SetToIdentity();

	//camPitch.SetToRotation(vertMovement, right.x, right.y, right.z);
	//camYaw.SetToRotation(horizMovement, 0, 1, 0);
	//rotation = camPitch * camYaw;

	//view = (rotation * view).Normalized();
	//target = (position + view);
	//up = rotation * up;

	//if (Application::IsKeyPressed(VK_LEFT)) //Look left
	//{
	//	float rotateView = (float)(70 * dt);
	//	rotation.SetToRotation(rotateView, defaultUp.x, defaultUp.y, defaultUp.z);
	//	right = view.Cross(up);
	//	right.y = 0;
	//	up = right.Cross(view);
	//	view = rotation * view;
	//	target = position + view;
	//}
	//if (Application::IsKeyPressed(VK_RIGHT)) //Look right
	//{
	//	float rotateView = (float)(70 * dt);
	//	rotation.SetToRotation(-rotateView, defaultUp.x, defaultUp.y, defaultUp.z);
	//	right = view.Cross(up);
	//	right.y = 0;
	//	up = right.Cross(view);
	//	view = rotation * view;
	//	target = position + view;
	//}
	//if (Application::IsKeyPressed(VK_UP)) //Look up
	//{
	//	float rotateView = (float)(50 * dt);
	//	right = view.Cross(up);
	//	right.y = 0;
	//	up = right.Cross(view);
	//	if (*rotateAngle <= 89)
	//	{
	//		rotation.SetToRotation(rotateView, right.x, right.y, right.z);
	//		view = rotation * view;
	//		target = position + view;
	//		*rotateAngle += 1;
	//	}
	//}
	//if (Application::IsKeyPressed(VK_DOWN)) //Look down
	//{
	//	float rotateView = (float)(50 * dt);
	//	right = view.Cross(up);
	//	right.y = 0;
	//	up = right.Cross(view);
	//	if (*rotateAngle >= -80)
	//	{
	//		rotation.SetToRotation(-rotateView, right.x, right.y, right.z);
	//		view = rotation * view;
	//		target = position + view;
	//		*rotateAngle -= 1;
	//	}
	//}
}


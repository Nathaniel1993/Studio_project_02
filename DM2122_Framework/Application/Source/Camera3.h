#ifndef CAMERA3_H
#define CAMERA3_H

#include "Camera.h"
#include "GameObject.h"
#include <vector>

extern std::vector<GameObject> AllSceneStaticObjects;
extern std::vector<GameObject> Scene02DoorContainer;
extern std::vector<GameObject> Scene03LeftDoorContainer;
extern std::vector<GameObject> Scene03RightDoorContainer;
extern std::vector<GameObject> CrateContainer;

class Camera3 : public Camera
{
public:
	Camera3();
	~Camera3();

	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	void Update(double dt, float *rotateAngle);
	Vector3 defaultUp;
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 view;
	Vector3 right;
	Vector3 tempPos;
	bool hit = false;
	bool shot = false;

	float rotateBody = 0.0f;
	float rotateArms = 0.0f;
	float rotateLegs = 0.0f;
	float rotateArmR = 0.0f;
	float rotateArmL = 0.0f;
	float rotateHandR = 0.0f;

	float yawLimit = 0.0f;
};

#endif
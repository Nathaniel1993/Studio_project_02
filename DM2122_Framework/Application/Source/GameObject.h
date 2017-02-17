#include "Vector3.h"

class GameObject
{
public:
	GameObject();
	GameObject(Vector3 newposition);
	GameObject(Vector3 newposition, int newsizeX, int newsizeY);
	~GameObject();
	Vector3 getPosition();
	void setPosition(Vector3 newPos);
	int getSizeX();
	int getSizeZ();

protected:
	Vector3 position_;
	int SizeX,
		SizeZ;
};
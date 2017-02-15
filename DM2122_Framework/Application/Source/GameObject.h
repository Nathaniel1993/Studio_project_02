#include "Vector3.h"

class GameObject
{
public:
	GameObject();
	GameObject(Vector3 newposition);
	GameObject(Vector3 newposition, int newsizeX, int newsizeY);
	~GameObject();
	Vector3 getPosition();
	int getSizeX();
	int getSizeY();

protected:
	Vector3 position_;
	int SizeX,
		SizeY;
};
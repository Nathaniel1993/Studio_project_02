#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"

class GameObject
{
public:
	//Constructor & Destructor
	GameObject();
	~GameObject();

protected:
	Vector3 position_;
};

#endif // !GAME_OBJECT_H

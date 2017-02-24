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
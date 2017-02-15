#include "GameObject.h"

GameObject::GameObject()
{
	position_ = Vector3(0, 0, 0);
	SizeX = 0;
	SizeY = 0;
}

GameObject::GameObject(Vector3 newposition)
{
	position_ = newposition;
	SizeX = 0;
	SizeY = 0;
}

GameObject::GameObject(Vector3 newposition, int newsizeX, int newsizeY)
{
	position_ = newposition;
	SizeX = newsizeX;
	SizeY = newsizeY;
}

GameObject::~GameObject()
{

}

Vector3 GameObject::getPosition()
{
	return position_;
}

int GameObject::getSizeX()
{
	return SizeX;
}

int GameObject::getSizeY()
{
	return SizeY;
}
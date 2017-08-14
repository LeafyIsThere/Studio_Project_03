
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	colliding(false),
	leftRight(false),
	mass(1.f),
	momentOfInertia(0),
	angularVelocity(0),
	color()
{
}

GameObject::~GameObject()
{
}
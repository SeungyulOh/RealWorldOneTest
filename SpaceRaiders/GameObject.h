#pragma once

#include <vector>
#include "Vector2D.h"

class PlayField;
class GameObject
{
public:
	char* m_objType = nullptr;
	Vector2D pos;
	unsigned char sprite;

	virtual void Update(PlayField& world) {};
	virtual bool DecreaseHealth() { return true; };
};
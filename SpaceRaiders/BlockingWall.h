#pragma once

#include "GameObject.h"

class BlockingWall : public GameObject
{
public:
	BlockingWall(unsigned int key, Vector2D SpawnLocation = Vector2D(0, 0));
	~BlockingWall();

	virtual void Callback_OnCollision(unsigned int targetuniquekey);
};
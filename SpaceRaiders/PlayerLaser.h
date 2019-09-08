#pragma once
#include "GameObject.h"

class PlayerLaser : public GameObject
{
public:
	PlayerLaser(unsigned int key, Vector2D SpawnLocation = Vector2D(0, 0));
	~PlayerLaser();

	virtual void Update(float DeltaTime) override;

	virtual void Callback_OnCollision(unsigned int targetuniquekey);
};
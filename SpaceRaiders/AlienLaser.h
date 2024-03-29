#pragma once

#include "GameObject.h"

class AlienLaser : public GameObject
{
public:
	AlienLaser(unsigned int key, Vector2D SpawnLocation = Vector2D(0, 0));
	~AlienLaser();

	virtual void BeginPlay() override;
	virtual void Update(float DeltaTime) override;
	virtual void Callback_OnCollision(unsigned int targetuniquekey);
};


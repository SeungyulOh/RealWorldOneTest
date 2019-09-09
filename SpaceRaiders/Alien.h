#pragma once

#include "GameObject.h"
#include "Vector2D.h"

class Alien : public GameObject
{
public:
	Alien(unsigned int key, Vector2D SpawnLocation = Vector2D(0, 0));
	~Alien();

public:
	virtual void BeginPlay() override;
	virtual void Update(float DeltaTime) override;
	virtual void Callback_OnCollision(unsigned int targetuniquekey) override;

private:
	void Transform();

private:
	enum AlienState
	{
		as_Normal,
		as_Better
	};

	// Variables dictating energy level for upgrade, direction of movement, and current speed
	float energy = 0.f;
	float firetime = 0.f;
	float firerate = 0.f;
	
	AlienState state = as_Normal;
	
};
#pragma once

#include "GameObject.h"

class Alien : public GameObject
{
public:
	Alien();
	~Alien();

protected:
	virtual void Update(PlayField& world) override;

public:
	void Transform();
	bool DecreaseHealth();

private:
	// Alien constants - these could move out into PlayField as configurable variables
	const float maxUpdateRate = 0.01f;
	const float transformEnergy = 1.f;
	
	enum AlienState
	{
		as_Normal,
		as_Better
	};

	// Variables dictating energy level for upgrade, direction of movement, and current speed
	float health = 1.f;
	float energy = 0.f;
	float direction = 1.f;
	float velocity = 0.5f;
	AlienState state;
	
};
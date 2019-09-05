#pragma once

#include "GameObject.h"

class PlayerShip : public GameObject
{
public:
	PlayerShip();
	~PlayerShip();

	virtual void Update(PlayField& world) override;
	
};
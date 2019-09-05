#pragma once

#include "GameObject.h"

class AlienLaser : public GameObject
{
public:
	AlienLaser();
	~AlienLaser();

	virtual void Update(PlayField& world) override;
};


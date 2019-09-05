#pragma once
#include "GameObject.h"

class PlayerLaser : public GameObject
{
public:
	PlayerLaser();
	~PlayerLaser();

	virtual void Update(PlayField& world) override;
};
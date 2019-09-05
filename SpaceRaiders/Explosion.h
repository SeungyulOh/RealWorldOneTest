#pragma once

#include "GameObject.h"

class Explosion : public GameObject
{
public:
	Explosion();
	~Explosion();

protected:
	virtual void Update(PlayField& world) override;

private:
	// Explosion lasts 5 ticks before it dissappears
	int timer = 5;
	
};
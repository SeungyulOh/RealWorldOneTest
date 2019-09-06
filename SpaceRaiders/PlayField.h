#pragma once

#include <vector>
#include "Vector2D.h"
#include <memory>
#include "PlayerLaser.h"

class GameObject;
class Input;
class PlayerLaser;

class PlayField
{
public:
	// Number of available active laser slots for aliens and player
	int AlienLasers = 10;
	int PlayerLasers = 4;

	void Update();
	
};
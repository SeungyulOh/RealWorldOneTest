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
private:
	typedef GameObject* GameObjPtr;
	std::vector<GameObjPtr> gameObjects;
public:
	Input* cotrollerInput = nullptr;
	Vector2D bounds;
	// Number of available active laser slots for aliens and player
	int AlienLasers = 10;
	int PlayerLasers = 4;

	PlayField(Vector2D iBounds) : bounds(iBounds) {};
	const std::vector<GameObjPtr>& GameObjects() { return gameObjects; }

	void Update();
	GameObject* GetPlayerObject();
	void SpawnLaser(GameObject* newObj);
	void DespawnLaser(GameObject* newObj);
	void AddObject(GameObject* newObj);
	void RemoveObject(GameObject* newObj);
	
};
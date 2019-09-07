#pragma once

#include <vector>
#include "Vector2D.h"
#include <memory>
#include "DelegateObject.h"

class GameObject;
class PlayerLaser;
class PlayField : public DelegateObject
{
public:
	PlayField();
	~PlayField();
public:
	virtual void Callback_OnStageChanged(int stage) override;
public:
	// Number of available active laser slots for aliens and player
	int AlienLasers = 10;
	int PlayerLasers = 4;

	bool Initialize();
	void Update(float DeltaTime);

private:
	void SpawnPlayer();
	void SpawnAliens(int stage);
};
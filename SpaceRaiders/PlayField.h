#pragma once

#include <vector>
#include "Vector2D.h"
#include <memory>
#include "DelegateObject.h"

/*
	This class has resposibility to spawn gameobjects such as
	player, alien, and blocking wall.

	holds variables to indicate the spawned count of alien and wall.
*/

class GameObject;
class PlayerLaser;
class PlayField : public DelegateObject
{
public:
	PlayField();
	~PlayField();
public:
	/* Delegate Callback Functions */
	virtual void Callback_OnStageChanged(int stage) override;
	virtual void Callback_OnAlienDestroyed(int score) override;
	virtual void Callback_OnWallDestroyed() override;
	/* Delegate Callback Functions End */

public:
	
	// Initial Settings - spawn player , binding delegates
	bool Initialize();

	// updates all spawned gameobjects
	void Update(float DeltaTime);

private:
	void SpawnPlayer();
	void SpawnAliens(int stage);
	void SpawnBlockingWall(int stage);

private:
	unsigned int CurrentAlientCount = 0;
	unsigned int CurrentWallCount = 0;
};
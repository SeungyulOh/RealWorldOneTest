#pragma once

#include "GameObject.h"
#include "DelegateObject.h"

class PlayerShip : public GameObject
{
public:
	PlayerShip(unsigned int key, Vector2D SpawnLocation = Vector2D(0, 0));
	~PlayerShip();

	virtual void BeginPlay() override;
	virtual void Update(float DeltaTime) override;
	
	virtual void Callback_OnLeftPressed() override;
	virtual void Callback_OnRightPressed() override;
};
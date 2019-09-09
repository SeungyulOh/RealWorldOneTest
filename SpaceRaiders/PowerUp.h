#pragma once

#include "GameObject.h"

enum EPowerUpType
{
	PU_MoveSpeed,
	PU_AttackSpeed,
	PU_Multishot,
	PU_None
};

class PlayerShip;
class PowerUp : public GameObject
{
	friend class PlayerShip;

public:
	PowerUp(unsigned int key, Vector2D SpawnLocation = Vector2D(0, 0));
	~PowerUp();

	virtual void BeginPlay() override;
	virtual void Update(float DeltaTime) override;
	virtual void Callback_OnCollision(unsigned int targetuniquekey) override;

public:
	EPowerUpType GetPowerUpType() const { return PowerupType; }

private:
	EPowerUpType PowerupType = PU_None;
	float PowerUpActivateTime = 0.f;
};
#pragma once

#include "GameObject.h"
#include "DelegateObject.h"
#include <queue>
#include "PowerUp.h"


struct FBuff
{
	FBuff() {}
	FBuff(EPowerUpType type, float duration) : Type(type), Duration(duration) {}

	EPowerUpType Type = PU_None;
	float Duration = 0.f;

	bool Update(float DeltaTime)
	{
		Duration -= DeltaTime;
		if (Duration < 0)
			return true;
		
		return false;
	}
};

class PlayerShip : public GameObject
{
public:
	PlayerShip(unsigned int key, Vector2D SpawnLocation = Vector2D(0, 0));
	~PlayerShip();

	virtual void BeginPlay() override;
	virtual void Update(float DeltaTime) override;
	
	virtual bool DecreaseHp() override;
	virtual void Callback_OnLeftPressed() override;
	virtual void Callback_OnRightPressed() override;
	virtual void Callback_OnFirePressed() override;
	virtual void Callback_OnCollision(unsigned int targetuniquekey) override;
private:
	void Process_SpawnLaser();

private:
	float firetime = 0.f;
	float firerate = 0.f;

	std::vector<FBuff> ActivatedBuff;
};
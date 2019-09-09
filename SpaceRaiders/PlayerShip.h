#pragma once

#include "GameObject.h"
#include "DelegateObject.h"
#include <queue>
#include "PowerUp.h"
#include <unordered_set>

struct FBuff
{
	FBuff() {}
	FBuff(EPowerUpType type, float duration) : Type(type), Duration(duration) 
	{}

	EPowerUpType Type = PU_None;
	float Duration = 0.f;

	bool operator == (FBuff const& rhs) const
	{
		return Type == rhs.Type;
	}

	bool Update(float DeltaTime);
	void Activate(float& firerate, Vector2D& velocity, bool& isMultishot);
	void DeActivate(float& firerate, Vector2D& velocity, bool& isMultishot);
};

struct KeyHasher_Buff
{
	std::size_t operator()(const FBuff& vec) const
	{
		return static_cast<size_t>(vec.Type);
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
	bool bMultiShot = false;

	std::unordered_set<FBuff , KeyHasher_Buff> ActivatedBuff;
};
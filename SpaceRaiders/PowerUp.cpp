#include "stdafx.h"
#include "PowerUp.h"
#include "GameObjectManager.h"
#include "RandomGeneratorHelper.h"

extern FConfig config;

PowerUp::PowerUp(unsigned int key, Vector2D SpawnLocation /*= Vector2D(0, 0)*/)
	:GameObject(key , SpawnLocation)
{
	type = GameObj_PowerUp;
	sprite = RS_PowerUp;

	PowerupType = static_cast<EPowerUpType>(RandomGeneratorHelper::GetIntRand(PU_MoveSpeed, PU_Multishot));
	PowerUpActivateTime = config.PowerUpActivateTime;
}

PowerUp::~PowerUp()
{

}

void PowerUp::BeginPlay()
{
	__super::BeginPlay();

	velocity.x = 0.f;
	velocity.y = config.PowerUpVelocityY;
}

void PowerUp::Update(float DeltaTime)
{
	__super::Update(DeltaTime);

	Region& worldregion = const_cast<Region&>(WorldRegion);

	Vector2D nextpos = pos + velocity * DeltaTime;
	if (worldregion.isIn(nextpos))
	{
		pos = nextpos;
	}
	else
	{
		Destroy();
		return;
	}
}

void PowerUp::Callback_OnCollision(unsigned int targetuniquekey)
{
	const GameObject* TargetObject = GameObjectManager::GetInstance().GetGameObject(targetuniquekey);
	if (TargetObject)
	{
		EGameObjectType type = TargetObject->GetType();

		switch (type)
		{
		case GameObj_PlayerShip:
		{
			Destroy();
		}break;

		default:
			break;
		}
	}
}


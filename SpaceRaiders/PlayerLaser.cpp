#include "stdafx.h"
#include "PlayerLaser.h"
#include "PlayField.h"
#include "Explosion.h"
#include "Renderer.h"
#include "CommonHeader.h"
#include "GameObject.h"
#include "Delegate.h"
#include "GameObjectManager.h"

extern FConfig config;

PlayerLaser::PlayerLaser(unsigned int key, Vector2D SpawnLocation /*= Vector2D(0, 0)*/)
	:GameObject(key, SpawnLocation)
{
	type = GameObj_PlayerLaser;
	sprite = RS_PlayerLaser;
}

PlayerLaser::~PlayerLaser()
{
}

void PlayerLaser::BeginPlay()
{
	__super::BeginPlay();

}

void PlayerLaser::Update(float DeltaTime)
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

void PlayerLaser::Callback_OnCollision(unsigned int targetuniquekey)
{
	const GameObject* TargetObject = GameObjectManager::GetInstance().GetGameObject(targetuniquekey);
	if (TargetObject)
	{
		EGameObjectType type = TargetObject->GetType();

		switch (type)
		{
			case GameObj_AlienLaser:
			case GameObj_AlienShip:
			case GameObj_BlockingWall:
			{
				bool isDestroyed = DecreaseHp();
				if(isDestroyed)
				{
					//spawn explosion when this is destroyed.
					GameObjectManager::GetInstance().CreateGameObject<Explosion>(pos);
				}
			}break;

			default:
				break;
		}
	}
}


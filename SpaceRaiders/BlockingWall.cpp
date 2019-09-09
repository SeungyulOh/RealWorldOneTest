#include "stdafx.h"
#include "BlockingWall.h"
#include "GameObjectManager.h"
#include "DelegateManager.h"

extern FConfig config;

BlockingWall::BlockingWall(unsigned int key, Vector2D SpawnLocation /*= Vector2D(0, 0)*/)
	:GameObject(key, SpawnLocation)
{
	type = GameObj_BlockingWall;
	sprite = RS_BlockingWall;
	Hp = config.WallMaxHealth;
}

BlockingWall::~BlockingWall()
{

}

void BlockingWall::Callback_OnCollision(unsigned int targetuniquekey)
{
	const GameObject* TargetObject = GameObjectManager::GetInstance().GetGameObject(targetuniquekey);
	if (TargetObject)
	{
		EGameObjectType type = TargetObject->GetType();

		switch (type)
		{
		case GameObj_PlayerLaser:
		{
			bool isDestroyed = DecreaseHp();
			if (isDestroyed)
			{
				//update ui
				DelegateManager::GetInstance().OnWallDestroyed().Broadcast();
			}
		}break;

		default:
			break;
		}
	}
}


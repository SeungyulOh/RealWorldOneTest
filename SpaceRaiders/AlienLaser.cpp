#include "stdafx.h"
#include "AlienLaser.h"
#include "PlayField.h"
#include "Explosion.h"
#include "Renderer.h"
#include "CommonHeader.h"
#include "Delegate.h"
#include "GameObjectManager.h"

extern FConfig config;

AlienLaser::AlienLaser(unsigned int key, Vector2D SpawnLocation /*= Vector2D(0, 0)*/)
:GameObject(key, SpawnLocation)
{
	type = GameObj_AlienLaser;
	sprite = RS_AlienLaser;

	
}

AlienLaser::~AlienLaser()
{
}


void AlienLaser::BeginPlay()
{
	__super::BeginPlay();

	velocity.x = 0.f;
	velocity.y = config.AlienLaserVelocityY;
}

void AlienLaser::Update(float DeltaTime)
{
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

void AlienLaser::Callback_OnCollision(unsigned int targetuniquekey)
{
	const GameObject* TargetObject = GameObjectManager::GetInstance().GetGameObject(targetuniquekey);
	if (TargetObject)
	{
		EGameObjectType type = TargetObject->GetType();

		switch (type)
		{
		case GameObj_PlayerLaser:
		case GameObj_AlienShip:
		case GameObj_PlayerShip:
		{
			DecreaseHp();
		}break;

		default:
			break;
		}
	}
}


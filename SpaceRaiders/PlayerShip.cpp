#include "stdafx.h"
#include "PlayerShip.h"
#include "Renderer.h"
#include "PlayField.h"
#include "PlayerLaser.h"
#include "Input.h"
#include "DelegateManager.h"
#include "Delegate.h"
#include "GameObject.h"
#include "Region.h"
#include "DelegateObject.h"
#include <algorithm>
#include "GameObjectManager.h"
#include "RandomGeneratorHelper.h"
#include "PowerUp.h"
#include <memory>

extern FConfig config;

PlayerShip::PlayerShip(unsigned int key , Vector2D SpawnLocation)
	:GameObject(key, SpawnLocation)
{
	type = GameObj_PlayerShip;
	sprite = RS_Player;
	firerate = config.PlayerFireRate;
	velocity = Vector2D(1.f, 0.f);
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::BeginPlay()
{
	__super::BeginPlay();

	DelegateManager::GetInstance().OnLeftPressed().AddDynamic(this, CALLBACK_NOPARAM(&DelegateObject::Callback_OnLeftPressed));
	DelegateManager::GetInstance().OnRightPressed().AddDynamic(this, CALLBACK_NOPARAM(&DelegateObject::Callback_OnRightPressed));
	DelegateManager::GetInstance().OnFirePressed().AddDynamic(this, CALLBACK_NOPARAM(&DelegateObject::Callback_OnFirePressed));

}

void PlayerShip::Update(float DeltaTime)
{
	__super::Update(DeltaTime);

	firetime += DeltaTime;

	//Randomly spawns laser if isManualAttack is set to false
	if (!config.isManualAttack)
	{
		//Check possibility to spawn laser
		if (firetime >= firerate)
		{
			if (RandomGeneratorHelper::GetRandomSuccess())
			{
				Process_SpawnLaser();
			}
			firetime = 0.f;
		}
	}

	//Check Buffs
	/*for(std::vector<FBuff>::iterator it = ActivatedBuff.begin() ; it != ActivatedBuff.end() ; ++it)
	{
		if (it == ActivatedBuff.end())
			break;

		bool bDeactivated = it->Update(DeltaTime);
		if (bDeactivated)
		{
			ActivatedBuff.erase(it--);
			continue;
		}

	}*/
}

bool PlayerShip::DecreaseHp()
{
	__super::DecreaseHp();

	if (Hp <= 0)
	{
		DelegateManager::GetInstance().OnGameOver().Broadcast();
		return true;
	}

	return false;
}

void PlayerShip::Callback_OnLeftPressed()
{
	pos.x -= velocity.x;
	pos.x = max(WorldRegion.left, pos.x);
}

void PlayerShip::Callback_OnRightPressed()
{
	pos.x += velocity.x;
	pos.x = min(WorldRegion.right, pos.x);
}

void PlayerShip::Callback_OnFirePressed()
{
	if (firetime > firerate)
	{
		Process_SpawnLaser();
		firetime = 0.f;
	}
	
}

void PlayerShip::Callback_OnCollision(unsigned int targetuniquekey)
{
	const GameObject* TargetObject = GameObjectManager::GetInstance().GetGameObject(targetuniquekey);
	if (TargetObject)
	{
		EGameObjectType type = TargetObject->GetType();

		switch (type)
		{
			case GameObj_AlienLaser:
			case GameObj_AlienShip:
			{
				DecreaseHp();
			}break;

			case GameObj_PowerUp:
			{
				const PowerUp* powerup = dynamic_cast<const PowerUp*>(TargetObject);
				if (powerup)
				{
					ActivatedBuff.push_back(FBuff(powerup->GetPowerUpType(), config.PowerUpActivateTime));
				}
			}
				
			default:
				break;
		}
	}
}


void PlayerShip::Process_SpawnLaser()
{
	GameObjectManager::GetInstance().CreateGameObject<PlayerLaser>(Vector2D(pos.x, pos.y - 1));
}


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
	
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::BeginPlay()
{
	__super::BeginPlay();

	velocity = Vector2D(1.f, 0.f);

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

	//update activated buff and check if it is still activating
	std::vector<FBuff> RemovePendingBuffs;
	for (auto& element : ActivatedBuff)
	{
		FBuff& buff = const_cast<FBuff&>(element);
		bool bDeactivated = buff.Update(DeltaTime);
		if (bDeactivated)
		{
			RemovePendingBuffs.push_back(buff);
		}
	}

	//remove deactivated buffs in activatedbuff unordered_set.
	for (auto& element : RemovePendingBuffs)
	{
		auto& foundit = ActivatedBuff.find(element);
		if (foundit != ActivatedBuff.end())
		{
			FBuff& Deactivatedbuff = const_cast<FBuff&>(*foundit);
			Deactivatedbuff.DeActivate(firerate, velocity, bMultiShot);
			ActivatedBuff.erase(foundit);
		}
	}

	
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
					FBuff newbuff = FBuff(powerup->GetPowerUpType(), config.PowerUpActivateTime);
					
					//if there is the same buff, just update duration
					auto foundbuff = ActivatedBuff.find(newbuff);
					if (foundbuff != ActivatedBuff.end())
					{
						FBuff& targetbuff = const_cast<FBuff&>(*foundbuff);
						targetbuff.Duration = newbuff.Duration;
					}
					else
					{
						newbuff.Activate(firerate, velocity, bMultiShot);
						ActivatedBuff.emplace(newbuff);
					}
				}
			}
				
			default:
				break;
		}
	}
}


void PlayerShip::Process_SpawnLaser()
{
	if (bMultiShot)
	{
		Vector2D	OriginVelocity = Vector2D(0.f, -config.PlayerLaserVelocityY);
		GameObjectManager::GetInstance().CreateGameObject<PlayerLaser>(Vector2D(pos.x, pos.y - 1) , OriginVelocity);
		GameObjectManager::GetInstance().CreateGameObject<PlayerLaser>(Vector2D(pos.x, pos.y - 1), OriginVelocity.Rotate(4.f / PI));
		GameObjectManager::GetInstance().CreateGameObject<PlayerLaser>(Vector2D(pos.x, pos.y - 1), OriginVelocity.Rotate(-4.f / PI));
	}
	else
	{
		GameObjectManager::GetInstance().CreateGameObject<PlayerLaser>(Vector2D(pos.x, pos.y - 1), Vector2D(0.f, -config.PlayerLaserVelocityY));
	}
	
}

bool FBuff::Update(float DeltaTime)
{
	Duration -= DeltaTime;
	if (Duration < 0)
		return true;

	return false;
}

void FBuff::Activate(float& firerate, Vector2D& velocity, bool& isMultishot)
{
	switch (Type)
	{
	case PU_MoveSpeed:
		velocity = velocity * config.PowerUpMoveSpeedScale;
		break;

	case PU_AttackSpeed:
		firerate /= config.PowerUpAttackSpeedScale;
		break;

	case PU_Multishot:
		isMultishot = true;
		break;
	}
}

void FBuff::DeActivate(float& firerate, Vector2D& velocity, bool& isMultishot)
{
	switch (Type)
	{
	case PU_MoveSpeed:
		velocity = velocity / config.PowerUpMoveSpeedScale;
		break;

	case PU_AttackSpeed:
		firerate *= config.PowerUpAttackSpeedScale;
		break;

	case PU_Multishot:
		isMultishot = false;
		break;
	}
}

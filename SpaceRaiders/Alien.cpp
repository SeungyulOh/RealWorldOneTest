#include "stdafx.h"
#include "Alien.h"
#include "Renderer.h"
#include "PlayField.h"
#include "Explosion.h"
#include "AlienLaser.h"
#include "CommonHeader.h"
#include "Region.h"
#include "DelegateManager.h"
#include "RandomGeneratorHelper.h"
#include "GameObjectManager.h"
#include "PowerUp.h"

extern FConfig config;

Alien::Alien(unsigned int key, Vector2D SpawnLocation)
	:GameObject(key , SpawnLocation)
{
	type = GameObj_AlienShip;
	sprite = RS_Alien;
	velocity = Vector2D(config.AlienVelocityX, config.AlienVelocityY);
	firerate = config.AlienFireRate;
}

Alien::~Alien()
{
}

void Alien::Transform()
{
	state = as_Better;
	sprite = RS_BetterAlien;
	velocity = velocity * 2.f;
	Hp++;
	firerate /= 2.f;

}


void Alien::Update(float DeltaTime)
{
	if (false == WorldRegion.isInVertically(pos))
	{
		DelegateManager::GetInstance().OnGameOver().Broadcast();
		return;
	}

	if (WorldRegion.isInHorizontally(pos + (velocity * DeltaTime)))
	{
		pos = pos + (velocity * DeltaTime);
	}
	else
	{
		//apply opposite velocity
		velocity.x *= -1.f;
		pos = pos + (velocity * DeltaTime);
	}

	//Check possibility to spawn laser
	if (firetime >= firerate)
	{
		if (RandomGeneratorHelper::GetRandomSuccess())
		{
			GameObjectManager::GetInstance().CreateGameObject<AlienLaser>(Vector2D(pos.x, pos.y + 1));
		}
		firetime = 0.f;
	}
	else
	{
		firetime += DeltaTime;
	}


	//check possibility to transform
	if (state == as_Normal && energy >= config.AlienMaxTransformEnery)
	{
		//do transform
		if (RandomGeneratorHelper::GetRandomSuccess())
		{
			Transform();
		}
		energy = 0.f;
	}
	else
	{
		energy += RandomGeneratorHelper::GetFloatRand(0, 100) * 0.01f * config.AlienMaxUpdateRate * DeltaTime;
	}

}

void Alien::Callback_OnCollision(unsigned int targetuniquekey)
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
				//update score
				int score = state == as_Better ? 20 : 10;
				DelegateManager::GetInstance().OnAlienDestroyed().Broadcast(score);

				//check possibility to spawn powerup
				GameObjectManager::GetInstance().CreateGameObject<PowerUp>(Vector2D(pos.x, pos.y + 1));
			}
		}break;

		default:
			break;
		}
	}
}


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

extern FConfig config;

Alien::Alien(unsigned int key, Vector2D SpawnLocation)
	:GameObject(key , SpawnLocation)
{
	type = GameObj_AlienShip;
	sprite = RS_Alien;
	velocity = Vector2D(config.AlienVelocityX, config.AlienVelocityY);
}

Alien::~Alien()
{
}

void Alien::Transform()
{
	state = as_Better;
	sprite = RS_BetterAlien;
	//velocity *= 2.f;
}

void Alien::Update(float DeltaTime)
{
	Region& worldregion = const_cast<Region&>(WorldRegion);

	if (false == worldregion.isInVertically(pos))
	{
		DelegateManager::GetInstance().OnGameOver().Broadcast();
		return;
	}

	//if Alien is inside of game region, change current location
	if (worldregion.isInHorizontally(pos))
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
	if (firetime >= config.AlienFireRate)
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

	__super::Update(DeltaTime);

}


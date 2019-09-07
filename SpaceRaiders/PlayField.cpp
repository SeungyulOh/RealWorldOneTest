#include "stdafx.h"
#include "PlayField.h"
#include "GameObject.h"
#include <algorithm>
#include <memory>
#include "GameObjectManager.h"
#include "DelegateManager.h"
#include "Alien.h"
#include "RandomGeneratorHelper.h"

extern FConfig config;

PlayField::PlayField()
{
}

PlayField::~PlayField()
{

}

void PlayField::Callback_OnStageChanged(int stage)
{
	SpawnAliens(stage);
}

bool PlayField::Initialize()
{
	SpawnPlayer();

	DelegateManager::GetInstance().OnStageChanged().AddDynamic(this, CALLBACK_ONEPARAM_INT(&DelegateObject::Callback_OnStageChanged));
	
	return true;
}

void PlayField::Update(float DeltaTime)
{
	
	//Update list of active objects in the world
	GameObjectManager::GetInstance().Update(DeltaTime);

}

void PlayField::SpawnPlayer()
{
	GameObjectManager::GetInstance().CreateGameObject<PlayerShip>(Vector2D(WorldRegion.right / 2.f, static_cast<float>(WorldRegion.bottom)));
}

void PlayField::SpawnAliens(int stage)
{
	int SpawnCount = config.SpawnAlienCountPerStage;

	std::vector<int> LocationX = RandomGeneratorHelper::GetDifferentIntRand(0, static_cast<int>(WorldRegion.right), SpawnCount);

	// Spawn Monster.
	for (size_t i = 0; i < LocationX.size(); ++i)
	{
		Vector2D location = Vector2D(static_cast<float>(LocationX[i]), static_cast<float>(WorldRegion.top));
		GameObjectManager::GetInstance().CreateGameObject<Alien>(location);
	}
}


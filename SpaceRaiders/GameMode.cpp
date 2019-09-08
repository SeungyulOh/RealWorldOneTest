#include "stdafx.h"
#include "GameMode.h"
#include "GameObjectManager.h"
#include "PlayerShip.h"
#include "CommonHeader.h"
#include "RandomGeneratorHelper.h"
#include "Alien.h"
#include "DelegateManager.h"

extern FConfig config;

void GameMode::Callback_OnGameOver()
{
	isGameOver = true;
}

void GameMode::Callback_OnAlienDestroyed(int score)
{
	//update score
	CurrentScore += score;
	DelegateManager::GetInstance().OnScoreChanged().Broadcast(CurrentScore);

}

bool GameMode::Initialize()
{
	DelegateManager::GetInstance().OnGameOver().AddDynamic(this, CALLBACK_NOPARAM(&DelegateObject::Callback_OnGameOver));
	DelegateManager::GetInstance().OnAlienDestroyed().AddDynamic(this, CALLBACK_ONEPARAM_INT(&DelegateObject::Callback_OnAlienDestroyed));
	
	DelegateManager::GetInstance().OnStageChanged().Broadcast(CurrentStage);

	return true;
}

bool GameMode::Update(float DeltaTime)
{
	if (isGameOver == true)
	{
		return isGameOver;
	}
		
	TotalPlaySecond += DeltaTime;

	if (config.MaxPlaySecond != 0 && TotalPlaySecond > config.MaxPlaySecond)
	{
		// game over
		isGameOver = true;
	}
	else
	{
		ElapsedTime += DeltaTime;
		if (ElapsedTime > config.PlayTimePerStage)
		{
			NextStage();
			ElapsedTime = 0.f;
		}
	}

	return false;
}

void GameMode::NextStage()
{
	++CurrentStage;

	DelegateManager::GetInstance().OnStageChanged().Broadcast(CurrentStage);
}


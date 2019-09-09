#include "stdafx.h"
#include "DelegateManager.h"
#include "Delegate.h"

void DelegateManager::Initialize()
{
	LeftPressed = std::make_unique<Delegate>();
	RightPressed = std::make_unique<Delegate>();
	FirePressed = std::make_unique<Delegate>();
	StageChanged = std::make_unique<Delegate>();
	ScoreChanged = std::make_unique<Delegate>();
	GameOver = std::make_unique<Delegate>();
	AddRenderItem = std::make_unique<Delegate>();
	AlienDestroyed = std::make_unique<Delegate>();
	WallCountChanged = std::make_unique<Delegate>();
	AlienCountChanged = std::make_unique<Delegate>();
	WallDestroyed = std::make_unique<Delegate>();
	AtkSpeedRemainTime = std::make_unique<Delegate>();
	MovSpeedRemainTime = std::make_unique<Delegate>();
	MultiShotRemainTIme = std::make_unique<Delegate>();
}

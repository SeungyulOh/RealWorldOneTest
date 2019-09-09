#pragma once

#include <memory>
#include "Delegate.h"

/*
	this class contains Delegate objects as	holding unique_ptr of them.
	
	this class has a responsibility to create/delete delegate objects.
	if you want to bind any callback functions, 
	you should only access to delegate objects from this class.
	
*/

class DelegateManager
{
	//Singleton
	//this intances should be only one.
public:
	static DelegateManager& GetInstance()
	{
		static DelegateManager instance;
		return instance;
	}
private:
	DelegateManager() { Initialize(); }
public:
	DelegateManager(DelegateManager const&) = delete;
	void operator=(DelegateManager const&) = delete;

private:
	void Initialize();

public:
	Delegate& OnLeftPressed() { return (*LeftPressed.get()); }
	Delegate& OnRightPressed() { return (*RightPressed.get()); }
	Delegate& OnFirePressed() { return (*FirePressed.get()); }
	Delegate& OnStageChanged() { return (*StageChanged.get()); }
	Delegate& OnScoreChanged() { return (*ScoreChanged.get()); }
	Delegate& OnWallCountChanged() { return (*WallCountChanged.get()); }
	Delegate& OnAlienCountChanged() { return (*AlienCountChanged.get()); }
	Delegate& OnGameOver() { return (*GameOver.get()); }
	Delegate& OnAddRenderItem() { return (*AddRenderItem.get()); }
	Delegate& OnAlienDestroyed() { return (*AlienDestroyed.get()); }
	Delegate& OnWallDestroyed() { return (*WallDestroyed.get()); }
	Delegate& OnAtkSpeedRemainTime() { return (*AtkSpeedRemainTime.get()); }
	Delegate& OnMovSpeedRemainTime() { return (*MovSpeedRemainTime.get()); }
	Delegate& OnMultiShotRemainTime() { return (*MultiShotRemainTIme.get()); }

private:
	std::unique_ptr<Delegate> LeftPressed;
	std::unique_ptr<Delegate> RightPressed;
	std::unique_ptr<Delegate> FirePressed;
	std::unique_ptr<Delegate> StageChanged;
	std::unique_ptr<Delegate> ScoreChanged;
	std::unique_ptr<Delegate> WallCountChanged;
	std::unique_ptr<Delegate> AlienCountChanged;
	std::unique_ptr<Delegate> GameOver;
	std::unique_ptr<Delegate> AddRenderItem;
	std::unique_ptr<Delegate> AlienDestroyed;
	std::unique_ptr<Delegate> WallDestroyed;
	std::unique_ptr<Delegate> AtkSpeedRemainTime;
	std::unique_ptr<Delegate> MovSpeedRemainTime;
	std::unique_ptr<Delegate> MultiShotRemainTIme;
};
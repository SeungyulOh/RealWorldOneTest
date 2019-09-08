#pragma once

#include <memory>
#include "Delegate.h"

/*
	this class contains delegates which are related to userinput,
	holding unique_ptr of them.
	so we don't need to worry about deallocating memory.
*/

class DelegateManager
{
	//Singleton
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
	Delegate& OnGameOver() { return (*GameOver.get()); }
	Delegate& OnAddRenderItem() { return (*AddRenderItem.get()); }
	Delegate& OnAlienDestroyed() { return (*AlienDestroyed.get()); }
private:
	std::unique_ptr<Delegate> LeftPressed;
	std::unique_ptr<Delegate> RightPressed;
	std::unique_ptr<Delegate> FirePressed;
	std::unique_ptr<Delegate> StageChanged;
	std::unique_ptr<Delegate> ScoreChanged;
	std::unique_ptr<Delegate> GameOver;
	std::unique_ptr<Delegate> AddRenderItem;
	std::unique_ptr<Delegate> AlienDestroyed;
};
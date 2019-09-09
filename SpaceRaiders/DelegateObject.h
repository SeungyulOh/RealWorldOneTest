#pragma once
#include <memory>
#include "CommonHeader.h"

/*
	This class is base class which needs delegate callback functions.

	This is derived by std::enable_shared_from_this class,
	because this object will be managed by std::sharedptr.
*/

class Renderer;
class DelegateObject : public std::enable_shared_from_this<DelegateObject>
{
public:
	DelegateObject() {}
	virtual ~DelegateObject() {}
	
public:
	virtual void Callback_OnGameOver() {};
	virtual void Callback_OnLeftPressed() {};
	virtual void Callback_OnRightPressed() {};
	virtual void Callback_OnFirePressed() {};
	virtual void Callback_OnStageChanged(int stage) {};
	virtual void Callback_OnScoreChanged(int score) {};
	virtual void Callback_OnAlienCountChanged(int count) {};
	virtual void Callback_OnWallCountChanged(int count) {};
	virtual void Callback_OnAtkSpeedUpRemainSec(int sec) {};
	virtual void Callback_OnMovSpeedUpRemainSec(int sec) {};
	virtual void Callback_OnMultishotRemainSec(int sec) {};

	virtual void Callback_OnAddRenderItem(RenderItem item) {};
	virtual void Callback_OnCollision(unsigned int targetuniquekey) {};
	virtual void Callback_OnAlienDestroyed(int score) {};
	virtual void Callback_OnWallDestroyed() {};

	std::shared_ptr<DelegateObject> Shared() { return shared_from_this(); }
};

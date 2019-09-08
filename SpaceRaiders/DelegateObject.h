#pragma once
#include <memory>
#include "CommonHeader.h"

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
	virtual void Callback_OnAddRenderItem(RenderItem item) {};
	virtual void Callback_OnCollision(unsigned int targetuniquekey) {};
	virtual void Callback_OnAlienDestroyed(int score) {};
	std::shared_ptr<DelegateObject> Shared() { return shared_from_this(); }
};

#include "stdafx.h"
#include "DelegateManager.h"
#include "Delegate.h"

void DelegateManager::Initialize()
{
	LeftPressed = std::make_unique<Delegate>();
	RightPressed = std::make_unique<Delegate>();
	FirePressed = std::make_unique<Delegate>();
}

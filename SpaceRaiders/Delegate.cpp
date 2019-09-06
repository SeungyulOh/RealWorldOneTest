
#include "stdafx.h"
#include "Delegate.h"
#include "GameObject.h"

void Delegate::AddDynamic(GameObject* target, std::function<void(GameObject&)>& callback)
{
	Callbacks.push_back(FGameObject_Callback(target, callback));
}

void Delegate::Clear()
{
	Callbacks.clear();
}

void Delegate::Broadcast()
{
	for (auto& elem : Callbacks)
	{
		elem.Callback((*elem.Target.get()));
	}
}


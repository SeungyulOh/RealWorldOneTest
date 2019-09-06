#pragma once

#include <functional>
#include <list>
#include <memory>
#include "GameObject.h"

class GameObject;

/* 
	A structure holding shared pointer of GameObject 
	and it's Callback functions.
*/ 
struct FGameObject_Callback
{
	std::shared_ptr<GameObject> Target;
	std::function<void(GameObject&)> Callback;


	FGameObject_Callback() {}
	FGameObject_Callback(GameObject* target, std::function<void(GameObject&)>& callback)
	{
		Target = target->shared_from_this();
		Callback = callback;
	}
};


/*
	Trying to imitate UE4's multicast delegate system.
*/
class Delegate
{
public:
	virtual void AddDynamic(GameObject* target , std::function<void(GameObject&)>& callback);
	virtual void Clear();
	virtual void Broadcast();

protected:
	std::vector<FGameObject_Callback> Callbacks;
};
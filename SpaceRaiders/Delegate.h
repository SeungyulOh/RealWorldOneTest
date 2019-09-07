#pragma once

#include <functional>
#include <list>
#include <memory>
#include <vector>
#include "DelegateObject.h"


/* 
	A structure holding shared pointer of GameObject 
	and it's Callback functions.
*/ 
struct FCallback
{
	std::shared_ptr<DelegateObject> Target;
	std::function<void(DelegateObject&)> Callback;


	FCallback() {}
	FCallback(DelegateObject* target, std::function<void(DelegateObject&)>& callback)
	{
		Target = target->Shared();
		Callback = callback;
	}
};

struct FCallback_OneParam_int
{
	std::shared_ptr<DelegateObject> Target;
	std::function<void(DelegateObject& , int)> Callback;


	FCallback_OneParam_int() {}
	FCallback_OneParam_int(DelegateObject* target, std::function<void(DelegateObject& , int)>& callback)
	{
		Target = target->Shared();
		Callback = callback;
	}
};

struct FCallback_OneParam_Renderitem
{
	std::shared_ptr<DelegateObject> Target;
	std::function<void(DelegateObject&, RenderItem)> Callback;


	FCallback_OneParam_Renderitem() {}
	FCallback_OneParam_Renderitem(DelegateObject* target, std::function<void(DelegateObject&, RenderItem)>& callback)
	{
		Target = target->Shared();
		Callback = callback;
	}
};



/*
	Trying to imitate UE4's delegate system.
*/
class Delegate
{
public:
	virtual void Clear();

	virtual void AddDynamic(DelegateObject* target , std::function<void(DelegateObject&)>& callback);
	virtual void AddDynamic(DelegateObject* target, std::function<void(DelegateObject&, int)>& callback);
	virtual void Bind(DelegateObject* target, std::function<void(DelegateObject&, RenderItem)>& callback);
	
	virtual void Broadcast();
	virtual void Broadcast(int value);
	virtual void Execute(RenderItem item);
protected:
	std::vector<FCallback> Callbacks;
	std::vector<FCallback_OneParam_int> CallbacksOneParamInt;
	
	FCallback_OneParam_Renderitem CallbackOneParamRenderItem;
};
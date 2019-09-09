#pragma once

#include <functional>
#include <list>
#include <memory>
#include <vector>
#include "DelegateObject.h"


/* 
	A structure holding shared pointer of DelegateObject 
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

/*
	A structure holding shared pointer of DelegateObject
	and it's Callback functions with one int param.
*/
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

/*
	A structure holding shared pointer of DelegateObject
	and it's Callback functions with one param, Renderitem.
*/
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
	In order to reduce dependencies between objects,
	I decided to build delegate system 
	which has similar behavior of UE4's delegate system.
*/
class Delegate
{
public:
	// clear all delegates.
	virtual void Clear();

	// bind delegateobject dynamically with no parameter callback funtion.
	virtual void AddDynamic(DelegateObject* target , std::function<void(DelegateObject&)>& callback);
	
	// bind delegateobject dynamically with one parameter(int) callback funtion.
	virtual void AddDynamic(DelegateObject* target, std::function<void(DelegateObject&, int)>& callback);

	// Currently, this is only used for renderer to collect renderlist.
	virtual void Bind(DelegateObject* target, std::function<void(DelegateObject&, RenderItem)>& callback);
	
	// broadcast or execute binded-callback functions.
	virtual void Broadcast();
	virtual void Broadcast(int value);
	virtual void Execute(RenderItem item);

protected:
	std::vector<FCallback> Callbacks;
	std::vector<FCallback_OneParam_int> CallbacksOneParamInt;	
	FCallback_OneParam_Renderitem CallbackOneParamRenderItem;
};
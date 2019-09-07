
#include "stdafx.h"
#include "Delegate.h"
#include <vcruntime_typeinfo.h>
#include "Renderer.h"

void Delegate::AddDynamic(DelegateObject* target, std::function<void(DelegateObject&)>& callback)
{
	Callbacks.push_back(FCallback(target, callback));
}

void Delegate::AddDynamic(DelegateObject* target, std::function<void(DelegateObject&, int)>& callback)
{
	CallbacksOneParamInt.push_back(FCallback_OneParam_int(target, callback));
}

void Delegate::Bind(DelegateObject* target, std::function<void(DelegateObject&, RenderItem)>& callback)
{
	CallbackOneParamRenderItem = FCallback_OneParam_Renderitem(target, callback);
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

void Delegate::Broadcast(int value)
{
	for (auto& elem : CallbacksOneParamInt)
	{
		elem.Callback((*elem.Target.get()) , value);
	}
}

void Delegate::Execute(RenderItem item)
{
	CallbackOneParamRenderItem.Callback((*CallbackOneParamRenderItem.Target.get()), item);
}



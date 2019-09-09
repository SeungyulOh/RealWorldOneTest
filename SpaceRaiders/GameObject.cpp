#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "DelegateManager.h"
#include <memory>
#include "Delegate.h"

GameObject::GameObject()
{

}

GameObject::GameObject(unsigned int serial, Vector2D SpawnLocation)
: uniquekey(serial) , pos(SpawnLocation)
{
	Collision = std::make_unique<Delegate>();
}

GameObject::~GameObject()
{
	
}


void GameObject::BeginPlay()
{
	OnCollosion().AddDynamic(this, CALLBACK_ONEPARAM_INT(&DelegateObject::Callback_OnCollision));
}

bool GameObject::Destroy()
{
	DelegateManager::GetInstance().OnAddRenderItem().Execute(RenderItem(Prevpos, sprite, true));
	
	return GameObjectManager::GetInstance().RemoveGameObject(uniquekey);
}

bool GameObject::DecreaseHp()
{
	Hp--;
	if (Hp <= 0)
	{
		Destroy();
		return true;
	}

	return false;
}

Vector2D GameObject::GetIntPosition()
{
	int x = static_cast<int>(pos.x);
	int y = static_cast<int>(pos.y);

	return Vector2D(static_cast<float>(x), static_cast<float>(y));
}

void GameObject::UpdateRenderItemList()
{
	if (Prevpos.IntCmp(pos) == false)
	{
		// clear prev position.
		DelegateManager::GetInstance().OnAddRenderItem().Execute(RenderItem(Prevpos, sprite, true));
		Prevpos = pos;
	}

	DelegateManager::GetInstance().OnAddRenderItem().Execute(RenderItem(pos, sprite, false));
}

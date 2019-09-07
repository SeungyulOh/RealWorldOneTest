#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "DelegateManager.h"

GameObject::GameObject()
{

}

GameObject::GameObject(unsigned int serial, Vector2D SpawnLocation)
: uniquekey(serial) , pos(SpawnLocation)
{
}

GameObject::~GameObject()
{
	
}

void GameObject::Update(float DeltaTime)
{
	if (Prevpos.IntCmp(pos) == false)
	{
		DelegateManager::GetInstance().OnAddRenderItem().Execute(RenderItem(Prevpos, sprite, true));
		DelegateManager::GetInstance().OnAddRenderItem().Execute(RenderItem(pos, sprite, false));
		Prevpos = pos;
	}
}

bool GameObject::Destroy()
{
	DelegateManager::GetInstance().OnAddRenderItem().Execute(RenderItem(pos, sprite, true));
	
	return GameObjectManager::GetInstance().RemoveGameObject(uniquekey);
}

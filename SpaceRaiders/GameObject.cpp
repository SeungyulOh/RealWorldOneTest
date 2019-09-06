#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"

GameObject::GameObject()
{

}

GameObject::GameObject(unsigned int serial)
: uniquekey(serial)
{
	
}

GameObject::~GameObject()
{
	
}

bool GameObject::Destroy()
{
	return GameObjectManager::GetInstance().RemoveGameObject(uniquekey);
}

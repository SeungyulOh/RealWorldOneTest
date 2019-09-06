#include "stdafx.h"
#include "GameObjectManager.h"
#include <unordered_map>
#include "GameObject.h"

void GameObjectManager::Initialize()
{

}

bool GameObjectManager::RemoveGameObject(unsigned int targetkey)
{
	auto iter = ObjectMap.find(targetkey);
	if (iter != ObjectMap.end())
	{
		ObjectMap.erase(targetkey);
		return true;
	}

	return false;
}

template<typename T>
void GameObjectManager::CreateGameObject()
{
	++unitserial;
	ObjectMap.insert(unitserial, std::make_shared<T>(unitserial));
}

const GameObject* GameObjectManager::GetGameObject(unsigned int key)
{
	auto iter = ObjectMap.find(key);
	if (iter != ObjectMap.end())
	{
		return iter->second.get();
	}

	return nullptr;
}

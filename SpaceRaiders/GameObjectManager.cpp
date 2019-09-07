#include "stdafx.h"
#include "GameObjectManager.h"
#include <unordered_map>
#include "GameObject.h"


bool GameObjectManager::RemoveGameObject(unsigned int targetkey)
{
	RemovePendingObject.push_back(targetkey);
	return false;
}


void GameObjectManager::Update(float DeltaTime)
{
	for (auto& element : ObjectMap)
	{
		element.second->Update(DeltaTime);
	}

	for (auto& element : RemovePendingObject)
	{
		auto iter = ObjectMap.find(element);
		if (iter != ObjectMap.end())
		{
			ObjectMap.erase(element);
		}
	}
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


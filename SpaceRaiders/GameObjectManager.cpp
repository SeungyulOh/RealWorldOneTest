#include "stdafx.h"
#include "GameObjectManager.h"
#include <unordered_map>
#include "GameObject.h"
#include <map>
#include "Vector2D.h"
#include "Delegate.h"

struct KeyHasher
{
	std::size_t operator()(const Vector2D& vec) const
	{
		int x = static_cast<int>(vec.x);
		int y = static_cast<int>(vec.y);
		return (x + y) * (x + y + 1) / 2 + x;
	}
};

bool GameObjectManager::RemoveGameObject(unsigned int targetkey)
{
	RemovePendingObject.push_back(targetkey);
	return false;
}


void GameObjectManager::CollisionCheck()
{
	//Collision Check
	std::unordered_multimap<Vector2D, unsigned int, KeyHasher> CollisionMultimap;
	for (auto& element : ObjectMap)
	{
		CollisionMultimap.emplace(element.second->GetIntPosition(), element.first);
	}

	for (auto& element : CollisionMultimap)
	{
		size_t count = CollisionMultimap.count(element.first);
		if (count >= 2)
		{
			auto iter = CollisionMultimap.equal_range(element.first);
			//if there are over 3 objects which have the same position, just apply collision process to two of them.
			unsigned int CollisionTarget = 0;
			for (auto it = iter.first; it != iter.second; ++it)
			{
				if (it->second == element.second)
					continue;

				CollisionTarget = it->second;
				break;
			}

			GetGameObject(element.second)->OnCollosion().Broadcast(CollisionTarget);

		}
	}
}

void GameObjectManager::Update(float DeltaTime)
{
	//Updates all gameobjects
	for (auto& element : ObjectMap)
	{
		element.second->Update(DeltaTime);
	}
	
	CollisionCheck();

	//Remove Object after all objects are updated
	for (auto& element : RemovePendingObject)
	{
		auto iter = ObjectMap.find(element);
		if (iter != ObjectMap.end())
		{
			ObjectMap.erase(element);
		}
	}

	//Check if position is updated to new one.
	//if it is updated, add renderlist.
	for (auto& element : ObjectMap)
	{
		element.second->UpdateRenderItemList();
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


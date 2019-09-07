#pragma once

#include <unordered_map>
#include <memory>
#include "PlayerShip.h"
#include "Renderer.h"


/*
	this class contains instances of Gameobject,
*/
class GameObject;
class GameObjectManager
{
	friend class GameObject;
	friend class Renderer;

public:
	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}
private:
	GameObjectManager() {}
public:
	GameObjectManager(GameObjectManager const&) = delete;
	void operator=(GameObjectManager const&) = delete;

public:
	template<typename T>
	void CreateGameObject(Vector2D position);

	void Update(float DeltaTime);
	
private:
	const GameObject* GetGameObject(unsigned int key);
	bool RemoveGameObject(unsigned int targetkey);

private:
	//indicate total created GameObject number.
	unsigned int unitcreatedcount = 0;

	//unordered_map has O(1) performance in case of insert , erase and find.
	std::unordered_map<unsigned int, std::shared_ptr<GameObject>> ObjectMap;

	std::vector<unsigned int> RemovePendingObject;
};

template<typename T>
void GameObjectManager::CreateGameObject(Vector2D position)
{
	++unitcreatedcount;

	std::shared_ptr<T> SpawnedObj = std::make_shared<T>(unitcreatedcount , position);
	ObjectMap.emplace(unitcreatedcount, SpawnedObj);

	SpawnedObj->BeginPlay();
}


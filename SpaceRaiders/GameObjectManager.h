#pragma once

#include <unordered_map>
#include <memory>

class GameObject;
/*
	this class contains instances of Gameobject,
*/
class GameObjectManager
{
	friend class GameObject;

public:
	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}
private:
	GameObjectManager() { Initialize(); }
public:
	GameObjectManager(GameObjectManager const&) = delete;
	void operator=(GameObjectManager const&) = delete;

public:
	template<typename T>
	void CreateGameObject();

	const GameObject* GetGameObject(unsigned int key);

private:
	void Initialize();
	bool RemoveGameObject(unsigned int targetkey);

private:
	//indicate total created GameObject number.
	unsigned int unitserial = 0;

	//unordered_map has O(1) performance in case of finding.
	std::unordered_map<unsigned int, std::shared_ptr<GameObject>> ObjectMap;
};


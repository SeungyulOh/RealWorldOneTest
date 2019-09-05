#include "stdafx.h"
#include "PlayField.h"
#include "GameObject.h"
#include <algorithm>

void PlayField::Update()
{
	// Update list of active objects in the world
	for (auto it : gameObjects)
	{
		if (it != nullptr)
		{
			it->Update(*this);
		}
	}
}

GameObject* PlayField::GetPlayerObject()
{
	auto it = std::find_if(gameObjects.begin(), gameObjects.end(), [](GameObjPtr in) { return (strcmp(in->m_objType, "ot_PlayerShip") == 0); });
	if (it != gameObjects.end())
		return (*it);
	else
		return nullptr;
}

void PlayField::SpawnLaser(GameObject* newObj)
{
	if (strcmp(newObj->m_objType, "ot_AlienLaser") == 0)
		AlienLasers--;
	else if (strcmp(newObj->m_objType, "ot_PlayerLaser") == 0)
		PlayerLasers--;
	AddObject(newObj);
}

void PlayField::DespawnLaser(GameObject* newObj)
{
	if (strcmp(newObj->m_objType, "ot_AlienLaser") == 0)
		AlienLasers++;
	else if (strcmp(newObj->m_objType, "ot_PlayerLaser") == 0)
		PlayerLasers++;
	RemoveObject(newObj);
}

void PlayField::AddObject(GameObject* newObj)
{
	//gameObjectsToAdd.push_back(GameObjPtr(newObj));
	gameObjects.push_back(newObj);
}

void PlayField::RemoveObject(GameObject* newObj)
{
	//gameObjectsToRemove.push_back(newObj);
	auto it = std::find_if(gameObjects.begin(), gameObjects.end(), [&](GameObjPtr in) { return (in == newObj); });
	gameObjects.erase(it);
}

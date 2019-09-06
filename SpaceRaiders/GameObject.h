#pragma once

#include <vector>
#include "Vector2D.h"
#include <memory>

class PlayField;
class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject();
	GameObject(unsigned int serial);
	virtual ~GameObject();

	char* m_objType = nullptr;
	Vector2D pos;
	unsigned char sprite;

	// this is the only way to deallocate gameobject instance.
	virtual bool Destroy();

	virtual void Update(PlayField& world) {};
	virtual bool DecreaseHealth() { return true; };

protected:
	unsigned int uniquekey;
};


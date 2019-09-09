#pragma once

#include <vector>
#include "Vector2D.h"
#include <memory>
#include "DelegateObject.h"

enum EGameObjectType
{
	GameObj_AlienShip,
	GameObj_PlayerShip,
	GameObj_AlienLaser,
	GameObj_PlayerLaser,
	GameObj_Explosion,
	GameObj_BlockingWall,
	GameObj_PowerUp,
	GameObj_End
};

enum RaiderSprites
{
	RS_BackgroundTile = ' ',
	RS_Player = 'P',
	RS_Alien = 'A',
	RS_BetterAlien = 'B',
	RS_PlayerLaser = 'o',
	RS_AlienLaser = '|',
	RS_Explosion = '*',
	RS_BlockingWall = 'X',
	RS_PowerUp = '?'
};

/*
	This class is the base class which is spawnable in world.

	This objects is instantiated by GameObjectManager class only,
	and will be managed by std::shared_ptr.

	I prefer not to use new, delete operation, 
	because It can make a mistake and hard to manage objects,
	so I decided to manage every objects with smart-pointers.
*/

class PlayField;
class Delegate;
class GameObject : public DelegateObject
{
public:
	GameObject();
	GameObject(unsigned int serial , Vector2D SpawnLocation = Vector2D(0,0));
	virtual ~GameObject();

	// invoked right after this is spawned in world successfully
	virtual void BeginPlay();

	// update function
	virtual void Update(float DeltaTime) {};

	// this is the only way to deallocate gameobject instance.
	virtual bool Destroy();

	// return true if it is destroyed.
	virtual bool DecreaseHp();

	// check every ticks if world position is changed or not.
	// it it is changed, notify renderer to clear and draw this object.
	void UpdateRenderItemList();

protected:
	unsigned int uniquekey;
	Vector2D pos;
	Vector2D velocity;
	RaiderSprites sprite;
	EGameObjectType type = GameObj_End;
	Vector2D Prevpos;
	int Hp = 1;

	//holding information of collision target and callback funtions.
	std::unique_ptr<Delegate> Collision;


public:
	//	GETTER, SETTER	//
	unsigned int GetUniqueKey() { return uniquekey; }
	Vector2D GetPosition() { return pos; }
	Vector2D GetIntPosition();
	RaiderSprites GetSprite() { return sprite; }
	EGameObjectType GetType() const { return type; }
	Delegate& OnCollosion() const { return (*Collision.get()); }
	void SetInitialVelocity(Vector2D initvec) { velocity = initvec; }
	
};


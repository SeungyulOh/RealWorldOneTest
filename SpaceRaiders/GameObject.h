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

class PlayField;
class Delegate;
class GameObject : public DelegateObject
{
public:
	GameObject();
	GameObject(unsigned int serial , Vector2D SpawnLocation = Vector2D(0,0));
	virtual ~GameObject();

	virtual void BeginPlay();
	

	virtual void Update(PlayField& world) {};
	virtual void Update(float DeltaTime) {};

	// this is the only way to deallocate gameobject instance.
	virtual bool Destroy();

	// return true if it is destroyed.
	virtual bool DecreaseHp();

	unsigned int GetUniqueKey() { return uniquekey; }
	Vector2D GetPosition() { return pos; }
	Vector2D GetIntPosition();
	RaiderSprites GetSprite() { return sprite; }
	EGameObjectType GetType() const  { return type; }
	Delegate& OnCollosion() const { return (*Collision.get()); }
	void SetInitialVelocity(Vector2D initvec) {	velocity = initvec; }
	void UpdateRenderItemList();

protected:
	unsigned int uniquekey;
	Vector2D pos;
	Vector2D velocity;
	RaiderSprites sprite;
	EGameObjectType type = GameObj_End;
	Vector2D Prevpos;
	int Hp = 1;

	std::unique_ptr<Delegate> Collision;
};


#pragma once
#include "Vector2D.h"
#include "Region.h"
#include <vector>

struct FConfig
{
	//global
	int Seed = 1;
	float  MaxPlaySecond = 0;
	bool isManualAttack = false;

	//Gamemode
	float PlayTimePerStage = 0;
	float SpawnAlienCountPerStage = 5;

	//Alien
	float AlienMaxUpdateRate = 0.01f;
	float AlienMaxTransformEnery = 1.f;
	float AlienMaxHealth = 1.f;
	float AlienVelocityX = 0.5f;
	float AlienVelocityY = 0.01f;
	float AlienFireRate = 1.f;

	//AlienLaser
	float AlienLaserVelocityY = 0.f;

	//Player
	float	PlayerFireRate = 0.f;

	//PlayerLaser
	float PlayerLaserVelocityY = 0.f;

	//Explosion
	int ExplosionSpawnCount = 0;
	float ExplosionLifeTime = 0.f;

	//BlockingWall
	int WallMaxHealth = 0;

	//PowerUp
	float PowerUpVelocityY = 0.f;
	float PowerUpActivateTime = 5.f;
	float PowerUpMoveSpeedScale = 1.5f;
	float PowerUpAttackSpeedScale = 2.f;
};

struct RenderItem
{
	RenderItem(const Vector2D& iPos, unsigned char iSprite, bool isClear) : pos(iPos), sprite(iSprite), bClear(isClear) {};
	Vector2D pos;
	unsigned char sprite;
	bool bClear;
};
typedef std::vector<RenderItem> RenderItemList;

const int SizeX = 80;
const int SizeY = 28;

const Region WorldRegion(0, 2, SizeX - 1, SizeY - 1);
const Region UIRegion(0, 0, SizeX - 1, 1);
const Region GameOverRegion(SizeX / 4, SizeY / 2 - 2, (3* SizeX) / 4, SizeY / 2 + 2);

#define PI 3.14f
#define CALLBACK_NOPARAM				std::function<void(DelegateObject&)> 
#define CALLBACK_ONEPARAM_INT			std::function<void(DelegateObject&, int)> 
#define CALLBACK_ONEPARAM_RENDERITEM	std::function<void(DelegateObject&, RenderItem)> 
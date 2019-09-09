#pragma once
#include "Vector2D.h"
#include "Region.h"
#include <vector>

struct FConfig
{
	//random seed
	int Seed = 1;
	
	//if you set this value non-zero, this game will end after this value is reached
	float  MaxPlaySecond = 0;
	
	//VK_SPACE key will be used to shoot playerlaser if you set to true, 
	//Otherwise playerlaser will be spawned randomly
	bool isManualAttack = false;

	//interval(sec) to next stage
	float PlayTimePerStage = 0;
	//Alien will be increased exponentially and this value will be the base.
	float SpawnAlienCountPerStage = 5;

	//Alien eneryrate to transform better alien
	float AlienMaxUpdateRate = 0.01f;
	//Alien MaxTransform energy value
	float AlienMaxTransformEnery = 1.f;
	float AlienMaxHealth = 1.f;
	float AlienVelocityX = 0.5f;
	float AlienVelocityY = 0.01f;
	//Alien Attack Speed Value
	float AlienFireRate = 1.f;

	//AlienLaser Velocity
	float AlienLaserVelocityY = 0.f;

	//Player Attack Speed Value
	float	PlayerFireRate = 0.f;

	//PlayerLaser Velocity
	float PlayerLaserVelocityY = 0.f;

	//Explosion spawns multi-subexplosion object using this number
	int ExplosionSpawnCount = 0;
	//Explosion LifeTime
	float ExplosionLifeTime = 0.f;

	//BlockingWall Hp
	int WallMaxHealth = 0;

	//PowerUp
	float PowerUpVelocityY = 0.f;
	float PowerUpActivateTime = 5.f;
	float PowerUpMoveSpeedScale = 1.5f;
	float PowerUpAttackSpeedScale = 2.f;
	float PowerUpSpawnProb = 0.f;
};

//Structure holding rendering-related values.
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
#include "stdafx.h"
#include "Explosion.h"
#include "Renderer.h"
#include "PlayField.h"
#include "CommonHeader.h"
#include "GameObjectManager.h"
#include "RandomGeneratorHelper.h"

extern FConfig config;

int SubExplosion::SpawnCount = 0;
Explosion::Explosion(unsigned int key, Vector2D SpawnLocation /*= Vector2D(0, 0)*/)
	:GameObject(key , SpawnLocation)
{
	type = GameObj_Explosion;
	sprite = RS_Explosion;
}

Explosion::~Explosion()
{
}

void Explosion::BeginPlay()
{
	__super::BeginPlay();

	for (int i = 0; i < config.ExplosionSpawnCount; ++i)
	{
		GameObjectManager::GetInstance().CreateGameObject<SubExplosion>(pos);
	}
	
	Destroy();
}

SubExplosion::SubExplosion(unsigned int key, Vector2D SpawnLocation /*= Vector2D(0, 0)*/)
	:GameObject(key , SpawnLocation)
{
	type = GameObj_Explosion;
	sprite = RS_Explosion;
	LifeTime = config.ExplosionLifeTime;
}

SubExplosion::~SubExplosion()
{

}

void SubExplosion::BeginPlay()
{
	__super::BeginPlay();

	++SpawnCount;
	int direction = SpawnCount % config.ExplosionSpawnCount;

	//decide direction 
	float radian = ((2 * PI) / config.ExplosionSpawnCount) * direction + (PI / 4.f);
	velocity = Vector2D(cosf(radian), sinf(radian));
	velocity = velocity * 10.f;
}

void SubExplosion::Update(float DeltaTime)
{
	__super::Update(DeltaTime);

	ElapsedTime += DeltaTime;
	if (ElapsedTime > LifeTime)
	{
		Destroy();
	}
	else
	{
		pos = pos + velocity * DeltaTime;
	}
}

void SubExplosion::SetVelocity(Vector2D vel)
{
	velocity = vel;
}

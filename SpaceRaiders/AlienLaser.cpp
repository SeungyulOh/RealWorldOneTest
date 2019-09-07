#include "stdafx.h"
#include "AlienLaser.h"
#include "PlayField.h"
#include "Explosion.h"
#include "Renderer.h"
#include "CommonHeader.h"

extern FConfig config;

AlienLaser::AlienLaser(unsigned int key, Vector2D SpawnLocation /*= Vector2D(0, 0)*/)
:GameObject(key, SpawnLocation)
{
	type = GameObj_AlienLaser;
	sprite = RS_AlienLaser;

	velocity.x = 0.f;
	velocity.y = config.AlienLaserVelocityY;
}

AlienLaser::~AlienLaser()
{
}


void AlienLaser::Update(float DeltaTime)
{
	Region& worldregion = const_cast<Region&>(WorldRegion);

	if (worldregion.isIn(pos))
	{
		pos.y += velocity.y * DeltaTime;
	}
	else
	{
		Destroy();
		return;
	}

	__super::Update(DeltaTime);
}


#pragma once

#include "GameObject.h"

class Explosion : public GameObject
{
public:
	Explosion(unsigned int key, Vector2D SpawnLocation = Vector2D(0, 0));
	~Explosion();

public:
	virtual void BeginPlay() override;
};

class SubExplosion : public GameObject
{
public:
	SubExplosion(unsigned int key, Vector2D SpawnLocation = Vector2D(0, 0));
	~SubExplosion();

public:
	virtual void BeginPlay() override;
	virtual void Update(float DeltaTime) override;

	void SetVelocity(Vector2D vel);

private:
	float LifeTime = 0.5f;
	float ElapsedTime = 0.f;
	static int SpawnCount;
};
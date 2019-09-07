#include "stdafx.h"
#include "Explosion.h"
#include "Renderer.h"
#include "PlayField.h"
#include "CommonHeader.h"

Explosion::Explosion()
{
	type = GameObj_Explosion;
	sprite = RS_Explosion;
}

Explosion::~Explosion()
{
}

void Explosion::Update(PlayField& world)
{
	__super::Update(world);

	/*timer--;
	if (!timer)
	{
		world.RemoveObject(this);
		delete this;
	}*/
}

#include "stdafx.h"
#include "PlayerLaser.h"
#include "PlayField.h"
#include "Explosion.h"
#include "Renderer.h"
#include "CommonHeader.h"


PlayerLaser::PlayerLaser()
{
	m_objType = new char[64]; 
	strcpy(m_objType, "ot_PlayerLaser"); 
	sprite = RS_PlayerLaser;
}

PlayerLaser::~PlayerLaser()
{
	delete[] m_objType;
}

void PlayerLaser::Update(PlayField& world)
{
	bool deleted = false;
	pos.y -= 1.f;
	if (pos.y < 0)
	{
		deleted = true;
	}

	for (auto it : world.GameObjects())
	{
		if (strcmp(it->m_objType, "ot_AlienShip") == 0 && it->pos.IntCmp(pos))
		{
			deleted = true;
			//Spawn explosion, kill the alien that we hit
			//ToDo - add scoring
			GameObject& no = *(new Explosion);
			no.pos = pos;
			world.AddObject(&no);
			if (it->DecreaseHealth())
				world.RemoveObject(it);
		}
	}

	if (deleted)
	{
		world.DespawnLaser(this);
		delete this;
	}
}


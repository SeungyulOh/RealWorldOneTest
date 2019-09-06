#include "stdafx.h"
#include "AlienLaser.h"
#include "PlayField.h"
#include "Explosion.h"
#include "Renderer.h"
#include "CommonHeader.h"

AlienLaser::AlienLaser()
{
	m_objType = new char[64]; 
	strcpy(m_objType, "ot_AlienLaser"); 
	sprite = RS_AlienLaser;
}

AlienLaser::~AlienLaser()
{
	delete[] m_objType;
}

void AlienLaser::Update(PlayField& world)
{
	__super::Update(world);

	bool deleted = false;
	pos.y += 1.f;
	//if (pos.y > world.bounds.y)
	//{
	//	deleted = true;
	//}
	//GameObject* player = world.GetPlayerObject();
	//if (player && pos.IntCmp(player->pos))
	//{
	//	deleted = true;
	//	//Spawn explosion, kill player
	//	GameObject& no = *(new Explosion);
	//	no.pos = pos;
	//	world.AddObject(&no);
	//	world.RemoveObject(player);
	//}

	if (deleted)
	{
		//world.DespawnLaser((GameObject*)this);
		delete this;
	}
}


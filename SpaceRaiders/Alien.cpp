#include "stdafx.h"
#include "Alien.h"
#include "Renderer.h"
#include "PlayField.h"
#include "Explosion.h"
#include "AlienLaser.h"
#include "CommonHeader.h"

Alien::Alien()
{
	m_objType = new char[64]; 
	strcpy(m_objType, "ot_AlienShip"); 
	sprite = RS_Alien; 
}

Alien::~Alien()
{
	delete m_objType;
}

void Alien::Transform()
{
	state = as_Better;
	sprite = RS_BetterAlien;
	velocity *= 2.f;
}

bool Alien::DecreaseHealth()
{
	health -= 1.f; 
	return health <= 0;
}

void Alien::Update(PlayField& world)
{
	pos.x += direction * velocity;
	// Border check
	//if (pos.x < 0 || pos.x >= world.bounds.x - 1)
	//{
	//	direction = -direction;
	//	pos.y += 1;
	//}

	//// Border check vertical:
	//if (pos.y >= world.bounds.y - 1)
	//{
	//	// kill player
	//	GameObject* player = world.GetPlayerObject();
	//	if (player && pos.IntCmp(player->pos))
	//	{
	//		//Spawn explosion
	//		GameObject& no = *(new Explosion);
	//		no.pos = pos;
	//		world.AddObject(&no);
	//		world.RemoveObject(player);
	//	}
	//}

	// Transform into better Alien
	if (state != as_Better)
	{
		/*floatRand updateRate(-maxUpdateRate, 2 * maxUpdateRate);
		energy += updateRate(rGen);
		if (energy >= transformEnergy)
			Transform();*/
	}

	//floatRand fireRate(0, 1);
	//if (fireRate(rGen) < 0.5 && world.AlienLasers > 0)
	//{
	//	//Spawn laser
	//	GameObject& newLaser = *(new AlienLaser);
	//	newLaser.pos = pos;
	//	world.SpawnLaser(&newLaser);
	//}
}


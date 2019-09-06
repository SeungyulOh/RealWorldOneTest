#include "stdafx.h"
#include "Explosion.h"
#include "Renderer.h"
#include "PlayField.h"
#include "CommonHeader.h"

Explosion::Explosion()
{
	m_objType = new char[64];  
	strcpy(m_objType, "ot_Explosion"); 
	sprite = RS_Explosion;
}

Explosion::~Explosion()
{
	delete[] m_objType;
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

#include "stdafx.h"
#include "PlayerShip.h"
#include "Renderer.h"
#include "PlayField.h"
#include "PlayerLaser.h"
#include "Input.h"
#include "DelegateManager.h"
#include "Delegate.h"
#include "GameObject.h"
#include "Region.h"
#include "DelegateObject.h"

PlayerShip::PlayerShip(unsigned int key , Vector2D SpawnLocation)
	:GameObject(key, SpawnLocation)
{
	type = GameObj_PlayerShip;
	sprite = RS_Player;

}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::BeginPlay()
{
	__super::BeginPlay();

	DelegateManager::GetInstance().OnLeftPressed().AddDynamic(this, CALLBACK_NOPARAM(&DelegateObject::Callback_OnLeftPressed));
	DelegateManager::GetInstance().OnLeftPressed().AddDynamic(this, CALLBACK_NOPARAM(&DelegateObject::Callback_OnRightPressed));
}

void PlayerShip::Update(float DeltaTime)
{
	__super::Update(DeltaTime);
}

void PlayerShip::Callback_OnLeftPressed()
{
}

void PlayerShip::Callback_OnRightPressed()
{

}


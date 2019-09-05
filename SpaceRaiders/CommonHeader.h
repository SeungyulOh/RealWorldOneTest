#pragma once

enum EGameObjectType
{
	GameObj_AlienShip,
	GameObj_PlayerShip,
	GameObj_AlienLaser,
	GameObj_PlayerLaser,
	GameObj_Explosion,
	GameObj_End
};

enum RaiderSprites
{
	RS_BackgroundTile = ' ',
	RS_Player = 'P',
	RS_Alien = 'A',
	RS_BetterAlien = 'B',
	RS_PlayerLaser = 0xBA,
	RS_AlienLaser = '|',
	RS_Explosion = '*'
};
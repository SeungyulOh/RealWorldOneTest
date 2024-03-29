// SpaceRaiders.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <vector>
#include <chrono>
#include <thread>
#include <memory>
#include <iostream>
#include "Vector2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "CommonHeader.h"
#include "PlayField.h"
#include "Alien.h"
#include "PlayerShip.h"
#include "Input.h"
#include <functional>
#include "RandomGeneratorHelper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <winnt.h>
#include <profileapi.h>
#include "GameMode.h"

using namespace std;



FConfig config;


#define ASSIGN_CONFIGVALUE(func , name , namestr , valuestr) 			\
if(namestr.compare(#name) == 0)	config.name = func(valuestr.c_str());
	
void ReadConfigData()
{
	ifstream configfile("config.txt");
	string str;
	if (configfile.is_open())
	{
		while (configfile)
		{
			getline(configfile, str);
			size_t pos = str.find('=');
			string namestr = str.substr(0, pos - 1);
			string valuestr = str.substr(pos + 1);
			ASSIGN_CONFIGVALUE(atoi, Seed, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, MaxPlaySecond, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, PlayTimePerStage, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, SpawnAlienCountPerStage, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, AlienMaxUpdateRate, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, AlienMaxTransformEnery, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, AlienMaxHealth, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, AlienVelocityX, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, AlienVelocityY, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, AlienFireRate, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, AlienLaserVelocityY, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, PlayerFireRate, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, PlayerLaserVelocityY, namestr, valuestr);
			ASSIGN_CONFIGVALUE(atoi, ExplosionSpawnCount, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, ExplosionLifeTime, namestr, valuestr);
			ASSIGN_CONFIGVALUE((bool)atoi, isManualAttack, namestr, valuestr);
			ASSIGN_CONFIGVALUE(atoi, WallMaxHealth, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, PowerUpVelocityY, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, PowerUpActivateTime, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, PowerUpMoveSpeedScale, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, PowerUpAttackSpeedScale, namestr, valuestr);
			ASSIGN_CONFIGVALUE((float)atof, PowerUpSpawnProb, namestr, valuestr);
		}
	}
}

int main()
{
	//Read Config Data.
	ReadConfigData();

	//seeding
	RandomGeneratorHelper::Seed(config.Seed);

	KeyboardInput Userinput;

	//Renderer settings
	std::shared_ptr<Renderer> RendererPtr = std::make_shared<Renderer>(Vector2D(static_cast<float>(SizeX), static_cast<float>(SizeY)));
	if (false == RendererPtr->Initialize())
	{
		std::cout << "Failed : RendererPtr->Initialize()" << std::endl;
		return -1;
	}

	//World settings
	std::shared_ptr<PlayField> WorldPtr = std::make_shared<PlayField>();
	if (false == WorldPtr->Initialize())
	{
		std::cout << "WorldPtr->Initialize()" << std::endl;
		return -1;
	}

	//GameMode settings
	std::shared_ptr<GameMode> GameModePtr = std::make_shared<GameMode>();
	if (false == GameModePtr->Initialize())
	{
		std::cout << "Failed :GameModePtr->Initialize()" << std::endl;
		return -1;
	}

	LARGE_INTEGER FrameTime;
	QueryPerformanceCounter(&FrameTime);
	LARGE_INTEGER FixTime;
	QueryPerformanceCounter(&FixTime);
	LARGE_INTEGER LastTime;
	QueryPerformanceCounter(&LastTime);
	LARGE_INTEGER CpuTick;
	QueryPerformanceFrequency(&CpuTick);

	while (true)
	{
		QueryPerformanceCounter(&FrameTime);
		if ((FrameTime.QuadPart - LastTime.QuadPart) > CpuTick.QuadPart)
		{
			QueryPerformanceFrequency(&CpuTick);
			LastTime = FrameTime;
		}

		float DeltaTime = static_cast<float>(FrameTime.QuadPart - FixTime.QuadPart) / static_cast<float>(CpuTick.QuadPart);
		FixTime = FrameTime;

		bool bGameOver = GameModePtr->Update(DeltaTime);
		if (bGameOver)
		{
			break;
		}

		Userinput.Update(DeltaTime);

		WorldPtr->Update(DeltaTime);

		RendererPtr->Update(DeltaTime);

		// Sleep a bit so updates don't run too fast
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	std::cin.get();
	return 0;
}


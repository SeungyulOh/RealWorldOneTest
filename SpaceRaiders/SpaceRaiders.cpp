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

using namespace std;

struct FConfig
{
	unsigned int Seed = 1;
	unsigned int MaxTickCount = 0;
	unsigned int SpawnAlienCountPerStage = 5;
};

FConfig config;
const Vector2D Worldsize(80, 28);

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
			if (namestr.compare("Seed") == 0)
			{
				config.Seed = atoi(valuestr.c_str());
			}
			if (namestr.compare("MaxTickCount") == 0)
			{
				config.MaxTickCount = atoi(valuestr.c_str());
			}
			if (namestr.compare("SpawnAlienCountPerStage") == 0)
			{
				config.SpawnAlienCountPerStage = atoi(valuestr.c_str());
			}
		}
	}
}

int main()
{
	//Read Config Data.
	ReadConfigData();

	//seeding
	RandomGeneratorHelper::Seed(config.Seed);

	//Renderer settings
	Renderer mainRenderer(Worldsize);
	if (false == mainRenderer.Initialize())
	{
		std::cout << "Failed : mainRenderer.Initialize()" << std::endl;
		return -1;
	}

	PlayField world;
	KeyboardInput userinput;
	while (true)
	{
		userinput.Update();

		world.Update();

		mainRenderer.Update();
	}
	
//
//	// Populate aliens
//	for (int k = 0; k < 20; k++)
//	{
//		Alien& a = *(new Alien);
//		a.pos.x = (float)xCoord(rGen);
//		a.pos.y = (float)yCoord(rGen);
//		world.AddObject(&a);
//	}
//	// Add player
//	PlayerShip& p = *(new PlayerShip);
//	p.pos = Vector2D(40, 27);
//	world.AddObject(&p);
//
//#define TEST_RUN
//#ifdef TEST_RUN
//	// Test run with random input
//	world.cotrollerInput = new RndInput;
//	for (int i = 0; i < 100; i++)
//#else
//	// ToDo - implement keyboard (or other device input)
//	//world.cotrollerInput = new KeyboardInput;
//	while (;;) // break when game-over
//#endif
//	{
//		world.Update();
//
//		RenderItemList rl;
//		for (auto it : world.GameObjects())
//		{
//			RenderItem a = RenderItem(Vector2D(it->pos), it->sprite );
//			rl.push_back(a);
//		}
//
//		mainRenderer.Update(rl);
//		// Sleep a bit so updates don't run too fast
//		std::this_thread::sleep_for(std::chrono::milliseconds(1));
//	}

	return 0;
}


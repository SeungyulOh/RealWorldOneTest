#include "stdafx.h"
#include <vector>
#include <iostream>
#include "Vector2D.h"
#include "Renderer.h"
#include <Windows.h>
#include "RandomGeneratorHelper.h"
#include "CommonHeader.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include <string>
#include "DelegateManager.h"

const COORD StageStrPosition = { 5 , 0 };
const COORD StageNumberPosition = { 15 , 0 };
const COORD ScoreStrPosition = { 25 , 0 };
const COORD ScoreNumberPosition = { 35 , 0 };
const COORD AlienCountStrPosition = { 45 , 0 };
const COORD AlienCountNumberPosition = { 55 , 0 };
const COORD WallCountStrPosition = { 65 , 0 };
const COORD WallCountNumberPosition = { 75 , 0 };

const COORD SpeedBuffStrPosition = { 5 , 28 };
const COORD SpeedBuffNumberPosition = { 20 , 28 };
const COORD AtkSpeedBuffStrPosition = { 30 , 28 };
const COORD AtkSpeedBuffNumberPosition = { 45 , 28 };
const COORD MultiShotStrPosition = { 55 , 28 };
const COORD MultiShotNumberPosition = { 70 , 28 };

Renderer::Renderer(const Vector2D& bounds)
: renderBounds(bounds)
{
	canvasSize = (int)(bounds.x * bounds.y);

	//allocated memory as much as the size of canvasSize.
	canvas.reserve(canvasSize);
	for (size_t i = 0; i < canvasSize; ++i)
	{
		canvas.push_back(0);
	}
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}


Renderer::~Renderer()
{
}


void Renderer::Callback_OnStageChanged(int stage)
{
	setCursorPosition(StageNumberPosition.X, StageNumberPosition.Y);
	std::cout << stage;
}

void Renderer::Callback_OnScoreChanged(int score)
{
	setCursorPosition(ScoreNumberPosition.X, ScoreNumberPosition.Y);
	std::cout << score;
}

void Renderer::Callback_OnGameOver()
{
	IsGameOver = true;

}

void Renderer::Callback_OnAddRenderItem(RenderItem item)
{
	if (item.bClear)
	{
		ClearRenderList.push_back(item);
	}
	else
	{
		DrawRenderList.push_back(item);
	}
}

void Renderer::Callback_OnAlienCountChanged(int count)
{
	setCursorPosition(AlienCountNumberPosition.X, AlienCountNumberPosition.Y);
	std::cout << count;
}

void Renderer::Callback_OnWallCountChanged(int count)
{
	setCursorPosition(WallCountNumberPosition.X, WallCountNumberPosition.Y);
	std::cout << count;
}

void Renderer::Callback_OnAtkSpeedUpRemainSec(int sec)
{
	setCursorPosition(AtkSpeedBuffNumberPosition.X, AtkSpeedBuffNumberPosition.Y);
	std::cout << sec << " sec";
}

void Renderer::Callback_OnMovSpeedUpRemainSec(int sec)
{
	setCursorPosition(SpeedBuffNumberPosition.X, SpeedBuffNumberPosition.Y);
	std::cout << sec << " sec";
}

void Renderer::Callback_OnMultishotRemainSec(int sec)
{
	setCursorPosition(MultiShotNumberPosition.X, MultiShotNumberPosition.Y);
	std::cout << sec << " sec";
}

bool Renderer::Initialize()
{
	if (false == AdjustConsoleSize())
		return false;

	if (false == HideCursor())
		return false;

	SetupUI();

	//Bind Delegate functions
	DelegateManager::GetInstance().OnStageChanged().AddDynamic(this, CALLBACK_ONEPARAM_INT(&DelegateObject::Callback_OnStageChanged));
	DelegateManager::GetInstance().OnScoreChanged().AddDynamic(this, CALLBACK_ONEPARAM_INT(&DelegateObject::Callback_OnScoreChanged));
	DelegateManager::GetInstance().OnGameOver().AddDynamic(this, CALLBACK_NOPARAM(&DelegateObject::Callback_OnGameOver));
	DelegateManager::GetInstance().OnAddRenderItem().Bind(this, CALLBACK_ONEPARAM_RENDERITEM(&DelegateObject::Callback_OnAddRenderItem));
	DelegateManager::GetInstance().OnAlienCountChanged().AddDynamic(this, CALLBACK_ONEPARAM_INT(&DelegateObject::Callback_OnAlienCountChanged));
	DelegateManager::GetInstance().OnWallCountChanged().AddDynamic(this, CALLBACK_ONEPARAM_INT(&DelegateObject::Callback_OnWallCountChanged));
	DelegateManager::GetInstance().OnMovSpeedRemainTime().AddDynamic(this, CALLBACK_ONEPARAM_INT(&DelegateObject::Callback_OnMovSpeedUpRemainSec));
	DelegateManager::GetInstance().OnAtkSpeedRemainTime().AddDynamic(this, CALLBACK_ONEPARAM_INT(&DelegateObject::Callback_OnAtkSpeedUpRemainSec));
	DelegateManager::GetInstance().OnMultiShotRemainTime().AddDynamic(this, CALLBACK_ONEPARAM_INT(&DelegateObject::Callback_OnMultishotRemainSec));
	return true;
}

void Renderer::Update(float DeltaTime)
{
	if (IsGameOver)
	{
		DrawGameOver();
	}
	else
	{
		ClearCanvas(RS_BackgroundTile);
		DrawCanvas();
	}
	
}

bool Renderer::AdjustConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO  info;
	GetConsoleScreenBufferInfo(hOut, &info);

	//our desired buffsize and windowRect size.
	COORD bufSize = { (SHORT)renderBounds.x, (SHORT)renderBounds.y + 1 };
	SMALL_RECT consoleWindowRect = { 0, 0, (SHORT)renderBounds.x - 1, (SHORT)renderBounds.y };

	// If the Current Buffer is Larger than what we want, Resize the 
	// Console Window First, then the Buffer 
	if ((DWORD)info.dwSize.X * info.dwSize.Y > (DWORD)bufSize.X * bufSize.Y)
	{
		if (!SetConsoleWindowInfo(hOut, TRUE, &consoleWindowRect))
		{
			return false;
		}

		if (!SetConsoleScreenBufferSize(hOut, bufSize))
		{
			return false;
		}
	}
	// If the Current Buffer is Smaller than what we want, Resize the 
	// Buffer First, then the Console Window 
	else if ((DWORD)info.dwSize.X * info.dwSize.Y < (DWORD)bufSize.X * bufSize.Y)
	{
		if (!SetConsoleScreenBufferSize(hOut, bufSize))
		{
			return false;
		}

		if (!SetConsoleWindowInfo(hOut, TRUE, &consoleWindowRect))
		{
			return false;
		}
	}
	else
	{
		// If the Current Buffer *is* the Size we want, Don't do anything! 
	}

	return true;
}


bool Renderer::HideCursor()
{
	//hide cursor
	CONSOLE_CURSOR_INFO cursorinfo;
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = false;
	return SetConsoleCursorInfo(hOut, &cursorinfo);
}

void Renderer::SetupUI()
{
	setCursorPosition(UIRegion.left, UIRegion.bottom);
	for (int i = 0; i <= UIRegion.right; ++i)
	{
		std::cout << '-';
	}

	//Draw UI
	setCursorPosition(StageStrPosition.X, StageStrPosition.Y);
	std::cout << "Stage : ";

	setCursorPosition(ScoreStrPosition.X, ScoreStrPosition.Y);
	std::cout << "Score : ";

	setCursorPosition(ScoreNumberPosition.X, ScoreNumberPosition.Y);
	std::cout << "0";

	setCursorPosition(AlienCountStrPosition.X, AlienCountStrPosition.Y);
	std::cout << "Alien : ";

	setCursorPosition(AlienCountNumberPosition.X, AlienCountNumberPosition.Y);
	std::cout << "0";

	setCursorPosition(WallCountStrPosition.X, WallCountStrPosition.Y);
	std::cout << "Wall : ";

	setCursorPosition(WallCountNumberPosition.X, WallCountNumberPosition.Y);
	std::cout << "0";

	setCursorPosition(SpeedBuffStrPosition.X, SpeedBuffStrPosition.Y);
	std::cout << "MovSpeedUp : ";

	setCursorPosition(SpeedBuffNumberPosition.X, SpeedBuffNumberPosition.Y);
	std::cout << "0 sec";

	setCursorPosition(AtkSpeedBuffStrPosition.X, AtkSpeedBuffStrPosition.Y);
	std::cout << "AtkSpeedUp : ";

	setCursorPosition(AtkSpeedBuffNumberPosition.X, AtkSpeedBuffNumberPosition.Y);
	std::cout << "0 sec";

	setCursorPosition(MultiShotStrPosition.X, MultiShotStrPosition.Y);
	std::cout << "Multishot : ";

	setCursorPosition(MultiShotNumberPosition.X, MultiShotNumberPosition.Y);
	std::cout << "0 sec";
}

void Renderer::setCursorPosition(int x, int y)
{
	COORD coord = { (SHORT)x, (SHORT)y };

	SetConsoleCursorPosition(hOut, coord);
}

void Renderer::ClearCanvas(unsigned char sprite)
{
	//don't want to iterate for-loop as much as canvasSize every frame
	//every updates, ClearRenderList is updated and read them to clear.
	for (auto& element : ClearRenderList)
	{
		int x = static_cast<int>(element.pos.x);
		int y = static_cast<int>(element.pos.y);
		if (x > WorldRegion.right || x < WorldRegion.left)
			continue;
		if (y < WorldRegion.top || y > WorldRegion.bottom)
			continue;

		size_t index = x + x* y;
		if (index >= 0 && index < canvasSize)
		{
			canvas[index] = sprite;
			setCursorPosition(x, y);
			std::cout << sprite;
		}
	}
	ClearRenderList.clear();
}

void Renderer::DrawCanvas()
{
	//DrawRenderList is also updated for every updates.
	for (auto& element : DrawRenderList)
	{
		int x = static_cast<int>(element.pos.x);
		int y = static_cast<int>(element.pos.y);
		if (x > WorldRegion.right || x < WorldRegion.left)
			continue;
		if (y < WorldRegion.top || y > WorldRegion.bottom)
			continue;

		//CachedRenderList
		size_t index = x + x * y;
		if (index >= 0 && index < canvasSize)
		{
			canvas[index] = element.sprite;
			setCursorPosition(x, y);
			std::cout << element.sprite;
		}

		
	}
	DrawRenderList.clear();

}

void Renderer::DrawGameOver()
{
	for (int y = GameOverRegion.top; y <= GameOverRegion.bottom; ++y)
	{
		for (int x = GameOverRegion.left; x <= GameOverRegion.right; ++x)
		{
			setCursorPosition(x, y);
			if (x == GameOverRegion.left || x == GameOverRegion.right
				|| y == GameOverRegion.top || y == GameOverRegion.bottom)
			{
				std::cout << '+';
			}
			else
			{
				std::cout << ' ';
			}

		}
	}

	int middleX = (GameOverRegion.left + GameOverRegion.right) / 2;
	int middleY = (GameOverRegion.top + GameOverRegion.bottom) / 2;

	std::string gameoverstring = "Game Over!";
	setCursorPosition(middleX - static_cast<int>(gameoverstring.size()) / 2, middleY - 1);
	std::cout << gameoverstring;

	std::string tempstring = "Press any buttons to quit";
	setCursorPosition(middleX - static_cast<int>(tempstring.size()) / 2, middleY + 1);
	std::cout << tempstring;
}


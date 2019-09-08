#include "stdafx.h"
#include <vector>
#include <iostream>
#include "Vector2D.h"
//#include "World.h"
#include "Renderer.h"
//#include "GameObject.h"
//#include "GameMode.h"
#include <Windows.h>
#include "RandomGeneratorHelper.h"
#include "CommonHeader.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include <string>
#include "DelegateManager.h"

const COORD StageStrPosition = { 0 , 0 };
const COORD StageNumberPosition = { 10 , 0 };
const COORD ScoreStrPosition = { 20 , 0 };
const COORD ScoreNumberPosition = { 30 , 0 };

Renderer::Renderer(const Vector2D& bounds)
: renderBounds(bounds)
{
	canvasSize = (int)(bounds.x * bounds.y);
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

	return true;
}

void Renderer::Update(float DeltaTime)
{
	ClearCanvas(RS_BackgroundTile);

	DrawCanvas();
}

bool Renderer::AdjustConsoleSize()
{
	// we are setting window height to m_renderBounds.y + 1 to avoid game screen jumping up and down because of 
	// inserting last character from m_canvas to console window (then cursor moves to new line that is beyond 
	// rendering area and when we invoke setCursorPosition(0, 0) all game screen jumps one character up)
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
}

void Renderer::setCursorPosition(int x, int y)
{
	COORD coord = { (SHORT)x, (SHORT)y };

	SetConsoleCursorPosition(hOut, coord);
}

void Renderer::ClearCanvas(unsigned char sprite)
{
	//don't want to iterate for-loop every frame
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


	//Draw GameObject
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


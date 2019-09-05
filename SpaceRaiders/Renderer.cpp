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



Renderer::Renderer(const Vector2D& bounds)
: renderBounds(bounds)
{
	canvasSize = (int)(bounds.x * bounds.y);
	canvas = new unsigned char[canvasSize];
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}


Renderer::~Renderer()
{
	delete[] canvas;
}


bool Renderer::Initialize()
{
	if (false == AdjustConsoleSize())
		return false;

	if (false == HideCursor())
		return false;

	return true;
}

void Renderer::Update(const RenderItemList& RenderList)
{
	FillCanvas(RS_BackgroundTile);



	//for (auto ri : RenderList)
	//{
	//	// std::cout << "object drawn" << std::endl;
	//	int x = int(ri.pos.x);
	//	int y = int(ri.pos.y);

	//	if (x >= 0 && x < renderBounds.x && y >= 0 && y < renderBounds.y)
	//	{
	//		*CurCanvas((int)ri.pos.x, + (int)ri.pos.y) = ri.sprite;
	//	}
	//}

	//DrawCanvas();
}


void Renderer::Update()
{
	FillCanvas(RS_BackgroundTile);

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
	COORD bufSize = { (SHORT)renderBounds.x, (SHORT)renderBounds.y };
	SMALL_RECT consoleWindowRect = { 0, 0, (SHORT)renderBounds.x - 1, (SHORT)renderBounds.y - 1 };

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

void Renderer::setCursorPosition(int x, int y)
{
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };

	SetConsoleCursorPosition(hOut, coord);
}

void Renderer::FillCanvas(unsigned char sprite)
{
	for (int i = 0; i < canvasSize; i++)
	{
		canvas[i] = sprite;
	}
}

void Renderer::DrawCanvas()
{
	//ToDo: Scoring output/tracking
	//GameMode* gameMode = world.GetGameMode();
	//if (gameMode)
	//	std::cout << "Score: " << gameMode->GetScore() << std::endl;

	for (int y = 0; y < renderBounds.y; y++)
	{
		for (int x = 0; x < renderBounds.x; x++)
		{
			setCursorPosition(x, y);
			//std::cout << *CurCanvas(x,y);

			if (RandomGeneratorHelper::GetIntRand(0, 9) % 8 == 0)
			{
				std::cout << "c";
			}
		}
		std::cout << std::endl;
	}
}


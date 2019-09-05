#pragma once

#include <vector>
#include <Windows.h>
#include <unordered_map>
#include "CommonHeader.h"

struct RenderItem
{
	RenderItem(const Vector2D& iPos, char iSprite) : pos(iPos), sprite(iSprite) {};
	Vector2D pos;
	char sprite;
};
typedef std::vector<RenderItem> RenderItemList;



class Renderer
{
public:
	Renderer(const Vector2D& bounds);
	~Renderer();

	// Initial Settings - console size, cursor visibility
	bool Initialize();
	// Draws all game objects after clearing filling the Canvas with _ symbol
	void Update(const RenderItemList& renderList);
	
	void setCursorPosition(int x, int y);
	

	void Update();
private:
	// Decides console size according to the desired size - renderBounds.
	bool AdjustConsoleSize();
	// Hide Console Cursor
	bool HideCursor();
	// Fills whole canvas array with sprite
	void FillCanvas(unsigned char sprite);
	// Prints canvas char array on console
	void DrawCanvas();

	const unsigned char* CurCanvas(int x, int y) { return &canvas[x + (int)renderBounds.x * y]; }


private:
	HANDLE hOut;
	Vector2D renderBounds;
	int canvasSize = 0;

	//one buffer looks okay. allocated 
	unsigned char* canvas = nullptr;

	//std::unordered_map<int, RaiderSprites> RenderList;
	//std::list<GameObject
	
};


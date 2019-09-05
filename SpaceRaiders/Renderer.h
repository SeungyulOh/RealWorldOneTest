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

	unsigned char* CurCanvas(int x, int y) { return &disp[curIdx % 2].canvas[x + (int)renderBounds.x * y]; }

	// Fills whole canvas array with sprite
	void FillCanvas(unsigned char sprite);

	// Prints canvas char array on console
	void DrawCanvas();

	void ClearCanvas();

private:
	HANDLE hOut;
	Vector2D renderBounds;
	int curIdx = 0;
	int canvasSize = 0;

	struct
	{
		unsigned char* canvas = nullptr;
	} disp[2]; // double buffer our canvas for no flicker display

	//std::unordered_map<int, RaiderSprites> RenderList;
	//std::list<GameObject
	
};


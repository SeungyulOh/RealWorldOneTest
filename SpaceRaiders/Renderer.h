#pragma once

#include <vector>
#include <Windows.h>
#include <unordered_map>
#include "CommonHeader.h"
#include "DelegateObject.h"


class Renderer : public DelegateObject
{
public:
	Renderer(const Vector2D& bounds);
	~Renderer();

	virtual void Callback_OnStageChanged(int stage) override;
	virtual void Callback_OnScoreChanged(int score) override;
	virtual void Callback_OnGameOver() override;
	virtual void Callback_OnAddRenderItem(RenderItem item) override;

	// Initial Settings - console size, cursor visibility
	bool Initialize();
	// Draws all game objects after clearing filling the Canvas with _ symbol
	void Update(float DeltaTime);
	
	void setCursorPosition(int x, int y);
	
	
private:
	// Decides console size according to the desired size - renderBounds.
	bool AdjustConsoleSize();
	// Hide Console Cursor
	bool HideCursor();

	void SetupUI();

	// Fills whole canvas array with sprite
	void ClearCanvas(unsigned char sprite);
	// Prints canvas char array on console
	void DrawCanvas();

	//const unsigned char* CurCanvas(int x, int y) { return &canvas.get()[x + (int)renderBounds.x * y]; }


private:
	HANDLE hOut;
	Vector2D renderBounds;
	int canvasSize = 0;

	int cachedStage = 1;
	int cachedScore = 0;

	//one buffer looks okay. 
	std::vector<unsigned char> canvas;

	//cache previous renderlist and clear them before drawing new renderlist.
	RenderItemList ClearRenderList;
	RenderItemList DrawRenderList;
	
};


#pragma once
#include "DelegateObject.h"

/*
	This class contains basic game info.
	stage info, current score

	This class checks whether game is over or not
*/

class GameMode : public DelegateObject
{
public:
	GameMode() {}
	~GameMode() {}

public:
	virtual void Callback_OnGameOver() override;
	virtual void Callback_OnAlienDestroyed(int score);
public:
	bool Initialize();
	bool Update(float DeltaTime);


private:
	void NextStage();

private:
	unsigned int CurrentStage = 1;
	unsigned int CurrentScore = 0;
	
	float TotalPlaySecond = 0.f;
	float ElapsedTime = 0.f;
	bool isGameOver = false;

};
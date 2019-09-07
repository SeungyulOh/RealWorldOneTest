#pragma once
#include "DelegateObject.h"



class GameMode : public DelegateObject
{
public:
	GameMode() {}
	~GameMode() {}

public:
	virtual void Callback_OnGameOver() override;
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
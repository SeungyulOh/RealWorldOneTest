#pragma once
#include "CommonHeader.h"

class Input
{
public:
	virtual void Update(float DeltaTime) = 0;
};



class RndInput : public Input
{
public:
	virtual void Update(float DeltaTime) override;
	/*virtual bool Left() { floatRand keyRate(0, 1); return (keyRate(rGen) < 0.3f); }
	virtual bool Right() { floatRand keyRate(0, 1); return (keyRate(rGen) < 0.4f); };
	virtual bool Fire() { floatRand keyRate(0, 1); return (keyRate(rGen) < 0.5f); };*/
};

class KeyboardInput : public Input
{
public:
	virtual void Update(float DeltaTime) override;
};

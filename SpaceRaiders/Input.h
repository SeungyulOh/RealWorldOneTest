#pragma once
#include "CommonHeader.h"

class Input
{
public:
	virtual void Update(float DeltaTime) = 0;
};


class KeyboardInput : public Input
{
public:
	virtual void Update(float DeltaTime) override;
};

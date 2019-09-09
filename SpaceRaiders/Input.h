#pragma once
#include "CommonHeader.h"


class Input
{
public:
	virtual void Update(float DeltaTime) = 0;
};


/*
	This class detects user's keyboard inputs.
	If it is successful in detecting, pre-subscribed delegate function will be invoked.
*/
class KeyboardInput : public Input
{
public:
	virtual void Update(float DeltaTime) override;
};

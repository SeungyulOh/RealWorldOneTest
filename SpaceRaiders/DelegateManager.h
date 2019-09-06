#pragma once

#include <memory>

class Delegate;
/*
	this class contains delegates which are related to userinput,
	holding unique_ptr of them.
	so we don't need to worry about deallocating memory.
*/

class DelegateManager
{
	//Singleton
public:
	static DelegateManager& GetInstance()
	{
		static DelegateManager instance;
		return instance;
	}
private:
	DelegateManager() { Initialize(); }
public:
	DelegateManager(DelegateManager const&) = delete;
	void operator=(DelegateManager const&) = delete;

private:
	void Initialize();

public:
	Delegate& OnLeftPressed() { return (*LeftPressed.get()); }
	Delegate& OnRightPressed() { return (*RightPressed.get()); }
	Delegate& OnFirePressed() { return (*FirePressed.get()); }
private:
	std::unique_ptr<Delegate> LeftPressed;
	std::unique_ptr<Delegate> RightPressed;
	std::unique_ptr<Delegate> FirePressed;
};
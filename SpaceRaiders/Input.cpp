#include "stdafx.h"
#include "Input.h"
#include <Windows.h>
#include <iostream>
#include "DelegateManager.h"
#include "Delegate.h"

void RndInput::Update(float DeltaTime)
{

}

void KeyboardInput::Update(float DeltaTime)
{
	static const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	if (hIn == INVALID_HANDLE_VALUE)
	{
		return;
	}

	DWORD eventnum = 0;
	if (!GetNumberOfConsoleInputEvents(hIn, &eventnum))
	{
		return;
	}

	DWORD readevent = 0;
	for (DWORD i = 0; i < eventnum; ++i)
	{
		INPUT_RECORD record;
		if (!ReadConsoleInput(hIn, &record, 1, &readevent))
		{
			continue;
		}

		if (record.EventType != KEY_EVENT)
		{
			continue;
		}

		if (record.Event.KeyEvent.bKeyDown == FALSE)
		{
			continue;
		}

		switch (record.Event.KeyEvent.wVirtualKeyCode)
		{
			case VK_LEFT:
			{
				DelegateManager::GetInstance().OnLeftPressed().Broadcast();
			}break;
			case VK_RIGHT:
			{
				DelegateManager::GetInstance().OnRightPressed().Broadcast();
			}break;
			default:
			{

			}break;
		}
	}
		
}

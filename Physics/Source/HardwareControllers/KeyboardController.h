#pragma once

#include <bitset>
#include <windows.h>

class KeyboardController
{
public:
	const static int MAX_KEYS = 256;

	static KeyboardController& GetInstance()
	{
		static KeyboardController keyboard;
		return keyboard;
	}

	// System Interface
	void UpdateKeyboardStatus(unsigned char _slot, bool _isPressed);
	void EndFrameUpdate();
	
	// User Interface
	bool IsKeyDown(unsigned char _slot);
	bool IsKeyUp(unsigned char _slot);
	bool IsKeyPressed(unsigned char _slot);
	bool IsKeyReleased(unsigned char _slot);

	KeyboardController();
	~KeyboardController();

	std::bitset<MAX_KEYS> currStatus, prevStatus;
};
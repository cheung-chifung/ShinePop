#pragma once

#ifndef InputManager_H
#endif InputManager_H

#include <windows.h>

/*
 * === INPUT ===
 */

#define KEY_UP 38
#define KEY_DOWN 40
#define KEY_LEFT 37
#define KEY_RIGHT 39
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_ESCAPE 27

typedef struct _INPUT_EVENT {
	bool keyPressed;
	WORD key;
	bool mouseClicked;
	COORD pos;
} INPUT_EVENT, *PINPUT_EVENT;

class InputManager
{
public:
	static InputManager* Instance ();
	const bool IsUsingKeyboard () const { return isUsingKeyboard; }
	INPUT_EVENT GetInputEvent();
private:
	InputManager ();
	InputManager ( InputManager const& );
	HANDLE hInConsole;
	INPUT_RECORD inputBuf[1];
	DWORD eventNum;
	bool isUsingKeyboard;
};

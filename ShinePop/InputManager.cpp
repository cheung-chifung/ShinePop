
#include "InputManager.h"

InputManager::InputManager()
{
	hInConsole = GetStdHandle ( STD_INPUT_HANDLE );

	DWORD wMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode ( hInConsole, wMode );

	isUsingKeyboard = false;
}

InputManager* InputManager::Instance ()
{
	static InputManager instance;
	return &instance;
}

/*
 * A simplified event processor for console application
 *
 */
INPUT_EVENT InputManager::GetInputEvent ()
{
	INPUT_EVENT _ie;
	_ie.keyPressed = false;
	_ie.mouseClicked = false;

	KEY_EVENT_RECORD ker;
	MOUSE_EVENT_RECORD mer;

	PeekConsoleInput( hInConsole, inputBuf, 1, &eventNum );
	if ( eventNum == 0 ) return _ie;
	ReadConsoleInput( hInConsole, inputBuf, 1, &eventNum );

	for ( DWORD i = 0; i < eventNum; i++ ) {
		switch ( inputBuf[i].EventType ) {
			case KEY_EVENT:
				ker = inputBuf[i].Event.KeyEvent;
				if ( ker.bKeyDown ) {
					_ie.keyPressed = true;
					_ie.key = inputBuf[i].Event.KeyEvent.wVirtualKeyCode;
					isUsingKeyboard = true;
				}
				break;
			case MOUSE_EVENT:
				mer = inputBuf[i].Event.MouseEvent;

				if ( mer.dwEventFlags == 0 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED ) { // button pressed
					_ie.mouseClicked = true;
					_ie.pos = mer.dwMousePosition;
					isUsingKeyboard = false;
				}
				break;
		}
	}
	return _ie;
}

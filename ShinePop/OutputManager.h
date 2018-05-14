#pragma once

#ifndef OutputManager_H
#define OutputManager_H

/*
 * === OUTPUT ===
 */
#define MAX_COLOR_COUNT 10

#define COLOR_CLEAR 0

#define LEFT_MARGIN 19
#define TOP_MARGIN 5

#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_YELLOW 6
#define COLOR_WHITE 7
#define COLOR_GRAY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_LIGHT_YELLOW 14
#define COLOR_BRIGHT_WHITE 15

// #define SCREEN_COUNT 2
#define SCREEN_COUNT 1

#include "GameSettings.h"
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

class OutputManager
{
public:
	static OutputManager* Instance ();
	void ClearScreen ();
	void SetColor ( unsigned char c );
	void HideCursor ();
	void GotoXY ( int x, int y );
	void ChangeTitle ( LPCTSTR title );
	void Print( const char* fmt, ... );
	void Print ( unsigned char c, int x, int y, const char* fmt, ... );
	void Print ( unsigned char c, const char* fmt, ... );
	void Print ( int x, int y, const char* fmt, ... );
	// void Refresh ();
	// void CopyBuffer ();
private:
	OutputManager ();
	OutputManager ( OutputManager const& );
	HANDLE hOutConsole;
	// COORD screenSize;
	COORD drawPos;
	
	HANDLE screen[SCREEN_COUNT];
	int curScreen;	
	char textBuffer[SCREEN_HEIGHT * SCREEN_WIDTH + 1];
	CHAR_INFO charBuffer[SCREEN_HEIGHT * SCREEN_WIDTH];
};

#endif

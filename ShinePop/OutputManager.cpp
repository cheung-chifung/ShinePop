
#include "OutputManager.h"

OutputManager::OutputManager()
{
	SMALL_RECT dispArea = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	COORD size = { SCREEN_WIDTH, SCREEN_HEIGHT };

	curScreen = 0;
	for( int i = 0; i < SCREEN_COUNT; i++ ) {
		if ( screen[i] ) free ( screen[i] );
		screen[i] = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, false, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
		
		SetConsoleScreenBufferSize( screen[i], size );	
		SetConsoleWindowInfo( screen[i], true, &dispArea );
		
	}

	SetConsoleActiveScreenBuffer ( screen[curScreen] );
	HideCursor();
}

OutputManager* OutputManager::Instance ()
{
	static OutputManager instance;
	return &instance;
}

void OutputManager::ClearScreen () {
	for( int i = 0; i < SCREEN_COUNT; i++ ) {
		COORD topLeft = { 0, 0 };
		CONSOLE_SCREEN_BUFFER_INFO screenInfo;
		DWORD written;
		GetConsoleScreenBufferInfo ( screen[i], &screenInfo );
		FillConsoleOutputCharacterA (
			screen[i], ' ', SCREEN_WIDTH * SCREEN_HEIGHT, topLeft, &written
		);
		FillConsoleOutputAttribute (
			screen[i], FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			SCREEN_WIDTH * SCREEN_HEIGHT,
			topLeft, &written
		);
	}
}

/*
 * 色を指定
 */
void OutputManager::SetColor(unsigned char c)
{
	SetConsoleTextAttribute ( screen[curScreen], c );
}

/*
 * カーソルを隠す
 */
void OutputManager::HideCursor()
{
	CONSOLE_CURSOR_INFO     cursorInfo;

	for( int i = 0; i < SCREEN_COUNT; i++ ) {
		GetConsoleCursorInfo ( screen[i], &cursorInfo );
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo ( screen[i], &cursorInfo );
	}
}

/*
 * カーソルを移動する
 */
void OutputManager::GotoXY(int x, int y)
{
	drawPos.X = x;
	drawPos.Y = y;
	SetConsoleCursorPosition ( screen[curScreen], drawPos );
}

void OutputManager::ChangeTitle ( LPCTSTR title )
{
	SetConsoleTitle ( title );
}

void OutputManager::Print ( const char* fmt, ... )
{
	va_list args;
	va_start ( args, fmt );
	vsprintf_s ( textBuffer, sizeof(textBuffer), fmt, args );
	va_end ( args );

	WriteConsole ( screen[curScreen], textBuffer, strlen(textBuffer), NULL, NULL );
}

void OutputManager::Print ( unsigned char c, int x, int y, const char* fmt, ... )
{
	SetColor ( c );
	GotoXY ( x, y );
	va_list args;
	va_start ( args, fmt );
	vsprintf_s ( textBuffer, sizeof(textBuffer), fmt, args );
	va_end ( args );
	WriteConsole ( screen[curScreen], textBuffer, strlen(textBuffer), NULL, NULL );
}

void OutputManager::Print ( unsigned char c, const char* fmt, ... )
{
	SetColor ( c );
	va_list args;
	va_start ( args, fmt );
	vsprintf_s ( textBuffer, sizeof(textBuffer), fmt, args );
	vprintf ( fmt, args );
	va_end ( args );
	WriteConsole ( screen[curScreen], textBuffer, strlen(textBuffer), NULL, NULL );
}

void OutputManager::Print ( int x, int y, const char* fmt, ... )
{
	GotoXY ( x, y );
	va_list args;
	va_start ( args, fmt );
	vsprintf_s ( textBuffer, sizeof(textBuffer), fmt, args );
	va_end ( args );
	WriteConsole ( screen[curScreen], textBuffer, strlen(textBuffer), NULL, NULL );
}
/*
void OutputManager::Refresh()
{
	COORD topLeft = { 0, 0 };
	SetConsoleActiveScreenBuffer ( screen[curScreen] );
	curScreen++;
	curScreen %= SCREEN_COUNT;
	SetConsoleCursorPosition ( screen[curScreen], topLeft );
}

void OutputManager::CopyBuffer()
{
	SMALL_RECT dispArea = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	COORD topLeft = { 0, 0 };
	COORD size = { SCREEN_WIDTH, SCREEN_HEIGHT };
	ReadConsoleOutput( screen[ (curScreen-1) % 2 ], charBuffer, size, topLeft, &dispArea );
	WriteConsoleOutput ( screen[ curScreen ], charBuffer,size, topLeft, &dispArea );
}
*/
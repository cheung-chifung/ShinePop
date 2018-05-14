
#include "GameManager.h"

GameManager::GameManager()
{
	om = om->Instance ();
	om->HideCursor ();
	om->ChangeTitle ( TEXT("★SHINE POP★") );

	ResetFrameCounter ();
}

void GameManager::ResetFrameCounter ()
{
	frameCount = 0;
	frameRawCount = 0;
	frameDuration = 1;
	lastUpdate = GetTickCount () ;
	lastFrameCount = 0;
	fps = FIXED_FPS;
}

GameManager* GameManager::Instance ()
{
	static GameManager instance;
	return &instance;
}

/*
 * ゲーム画面遷移
 */
void GameManager::ChangeGameState(GAME_STATE gs)
{
	if (gs != state) {
		om->ClearScreen();
		state = gs;
		if ( scene ) free ( scene );
		
		switch (gs) {
			case GAME_STATE_RESULT:
				scene = new GameResult ();
				break;
			case GAME_STATE_MAIN:
				scene = new GameMain ();
				break;
			case GAME_STATE_TITLE:
			default:
				scene = new GameTitle ();
				break;
		}
		scene->Start();
	}
}

/*
 * フレーム開始時呼ぶべき関数
 */
void GameManager::BeginFrame ()
{
	lastFrameBegin = GetTickCount ();
}

/*
 * フレーム終了時呼ぶべき関数
 */
void GameManager::EndFrame ()
{
	unsigned long timeDiff = GetTickCount() - lastFrameBegin;
	frameDuration = static_cast <int> ( std::floor( timeDiff / FIXED_FRAME_LENGTH ) ) + 1;
	sleepDuration = FIXED_FRAME_LENGTH - ( timeDiff - FIXED_FRAME_LENGTH * ( frameDuration - 1 ) ) ;


	frameCount += frameDuration;
	lastFrameCount += frameDuration;
	frameRawCount ++;
	int sleepDurationInt = static_cast <int> ( std::floor( sleepDuration ) ) ;
	sleepDurationInt +=  rand() % 100 > static_cast <int> ( std::floor ( (sleepDuration - sleepDurationInt) * 100 ) ) ? 0 : 1;
	
	// om->GotoXY ( 0, 0 );
	// om->Print ( "%2d,%8.2f,%4d,%4d", timeDiff, sleepDuration, sleepDurationInt, frameDuration );
	
	if ( sleepDuration >= 0 ) { Sleep ( sleepDurationInt ); }
}

/*
 * FPSを取得
 */
double GameManager::GetFPS ()
{
	unsigned long curTick = GetTickCount ();	
	if ( curTick - lastUpdate > UPDATE_SPEED ) {
		fps = (double) lastFrameCount * 1000 / ( curTick - lastUpdate );
		lastUpdate = curTick;
		lastFrameCount = 0;
	}
	return fps;
}
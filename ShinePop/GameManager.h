#pragma once

#ifndef GameManager_H
#define GameManager_H

#include "InputManager.h"
#include "OutputManager.h"
#include "Scene.h"
#include "GameTitle.h"
#include "GameResult.h"
#include "GameMain.h"

#include <windows.h>
#include <cmath>

enum GAME_STATE
{
	GAME_STATE_TITLE = 1,
	GAME_STATE_MAIN  = 2,
	GAME_STATE_RESULT = 3
};

#define FIXED_FPS 60
#define FIXED_FRAME_LENGTH ( 1000.0f / FIXED_FPS )

#define UPDATE_SPEED 1000

class GameManager
{
public:
	static GameManager* Instance ();
	void ChangeGameState ( GAME_STATE gs );
	int score;

	void BeginFrame ();
	void EndFrame ();
	unsigned int GetFrameDuration () { return frameDuration; };
	unsigned long GetFrameCount () { return frameCount; };
	unsigned long GetRawFrameCount () { return frameRawCount; }
	double GetFPS ();
	void ResetFrameCounter ();
private:
	GameManager ();
	GameManager ( GameManager const& );
	GAME_STATE state;
	Scene* scene;

	InputManager* im;
	OutputManager* om;

	unsigned long lastFrameBegin;
	double sleepDuration;
	double fps;
	unsigned long frameCount;
	unsigned long frameRawCount;
	unsigned int frameDuration;

	unsigned long lastUpdate;
	unsigned int lastFrameCount;
};

#endif
#pragma once

#ifndef GameResult_H
#define GameResult_H

#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "User32.lib")
#include "scene.h"

#include "GameSettings.h"

#include <windows.h>
#include <winreg.h>
#include <list>

#include "OutputManager.h"
#include "InputManager.h"

class GameResult :
	public Scene
{
public:
	GameResult ();
	void Start();

private:
	InputManager* im;
	OutputManager* om;
};

#endif

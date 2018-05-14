#pragma once

#ifndef GameTitle_H
#define GameTitle_H

#include "scene.h"

#include "OutputManager.h"
#include "InputManager.h"

class GameTitle :
	public Scene
{
public:
	GameTitle ();
	void Start();

private:
	InputManager* im;
	OutputManager* om;
};

#endif

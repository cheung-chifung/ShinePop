#pragma once

#ifndef TimeManager_H
#define TimeManager_H

#include <windows.h>

class TimeManager
{
public:
	static TimeManager* Instance ();
	void Start ();
	void Pause ( bool s );
	const bool IsPause () const { return isTimerPause; }
	unsigned long CurrentRawTick ();
	unsigned long CurrentTick ();
private:
	TimeManager ();
	TimeManager ( TimeManager const& );

	unsigned long lastTick;
	unsigned long lastPauseTime;
	unsigned long pauseDiff;
	bool isTimerPause;
};
#endif

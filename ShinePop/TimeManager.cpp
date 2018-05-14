
#include "TimeManager.h"

TimeManager::TimeManager(void)
{
}

TimeManager* TimeManager::Instance ()
{
	static TimeManager instance;
	return &instance;
}

void TimeManager::Start ()
{
	isTimerPause = false;
	lastTick = GetTickCount();
	lastPauseTime = lastTick;
	pauseDiff = 0;
}

/*
 * ゲーム開始からの時間（一時停止の時間を除く）
 */
unsigned long TimeManager::CurrentRawTick() {
	return GetTickCount() - lastTick;
}

/*
 * ゲーム開始からの時間
 */
unsigned long TimeManager::CurrentTick() {
	return GetTickCount() - pauseDiff - lastTick;
}

/*
 * 内部処理を一時停止
 *
 * @arg s: true for pause, false for play
 */

void TimeManager::Pause( bool s ) {
	isTimerPause = s;
	if ( s ) {
		lastPauseTime = GetTickCount();
	} else {
		pauseDiff += GetTickCount() - lastPauseTime;
	}
}

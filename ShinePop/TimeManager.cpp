
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
 * �Q�[���J�n����̎��ԁi�ꎞ��~�̎��Ԃ������j
 */
unsigned long TimeManager::CurrentRawTick() {
	return GetTickCount() - lastTick;
}

/*
 * �Q�[���J�n����̎���
 */
unsigned long TimeManager::CurrentTick() {
	return GetTickCount() - pauseDiff - lastTick;
}

/*
 * �����������ꎞ��~
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

#pragma once

#ifndef GameMain_H
#define GameMain_H

/*
 * === HEADER FILES ===
 */

#include <windows.h>
#include "GameManager.h"
#include "TimeManager.h"
#include "GameSettings.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <conio.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <queue>

enum SWAP_DIRECTION
{
	SWAP_DIRECTION_UNKNOWN = 0,
	SWAP_DIRECTION_LEFT = 1,
	SWAP_DIRECTION_RIGHT,
	SWAP_DIRECTION_UP,
	SWAP_DIRECTION_DOWN
};

#define SPECIAL_GEM_ID 255

enum GEM_TYPE
{
	GEM_TYPE_UNKNOWN = 0,
	GEM_TYPE_NORMAL = 1,
	GEM_TYPE_FOUR = 2, // �l�A��
	GEM_TYPE_FIVE = 3, // �ܘA��
	GEM_TYPE_CANDY = 4, // �L�����f�B�[�u���b�N
};

typedef unsigned char uchar;

typedef struct _GEM {
	uchar id;    // ���
	GEM_TYPE s;  // ����u���b�N�i�S�E�T�A��,etc�j
	uchar hc;    // ���A���u���b�N��
	uchar vc;    // �c�A���u���b�N��
	bool del;    // ������u���b�N���ǂ���
	bool redraw; // �`������
	uchar bid;   // �L�����f�B�[�u���b�N�p��ID�iGEM�̃I�u�W�F�N�g�����ׂ������j

	int yOffset; // �A�j���[�V�����p
 
} GEM, *PGEM;

#define DELETE_ANIM_DURATION 9
#define DELETE_KEY_FRAME_1 6
#define DELETE_KEY_FRAME_2 3

#define READY_DURATION 60
#define GO_DURATION 60

class GameManager;

class GameMain :
	public Scene
{
public:
	GameMain();
	~GameMain();
	void Start ();

private:
	bool Timer ();
	void SetScore ( int s );
	void IncScore ( int s );
	void DrawScore ( int s );

	void DrawReadyGo ();

	InputManager* im;
	OutputManager* om;

	TimeManager* tm;

	GameManager* gm;

	COORD curPos;
	bool selected;
	bool isFeverMode;
	bool isTimerPause;

	// �e��u���b�N�̌����W�v�p�i �� �j
	uchar gemStat[BOARD_GEM_COUNT];
	// �����p�m���e�[�u��
	uchar gemProbTable[BOARD_GEM_COUNT];

	unsigned long curTick;
	unsigned long feverEndTime;

	GEM _gems[BOARD_WIDTH][BOARD_HEIGHT];

	COORD pos[2]; //�@�Ō�ɐG�����u���b�N�̈ʒu
	
	unsigned long chgCols; // �e��������ABit Flags
	unsigned long chgRows; // �e�������s�ABit Flags
	unsigned long animCols; // �A�j�����o�����

	int lastDelete; // �A�j�����o�p
	int scoreGaugeValue; // �A�j�����o�p

	SWAP_DIRECTION direct;

	// �R���{���Ԃ̗���
	std::queue<unsigned long> comboLog;
	// �R���{��
	int comboCount;
	// �R���{�Q�[�W�̒l
	int comboGaugeValue;
	// �R���{�Q�[�W�̍Ō�ύX����
	unsigned long lastComboGaugeChanged;
	// �Ō�̌�������
	unsigned long lastSwap;
	COORD hintPos;

	static const byte colors[MAX_COLOR_COUNT];
	static const char tx[MAX_COLOR_COUNT][3];

	int Swap ( COORD oldPos, COORD newPos, bool isForceRecover = false );
	int Swap ( COORD oldPos, SWAP_DIRECTION d, bool isForceRecover = false );
	void PostProcessSwap ( COORD oldPos, COORD newPos );
	bool ProcessMatchLines ();
	void ProcessFalldown ( bool withAnim = true );
	void ProcessAnim ();
	void ProcessAllMatch ( );
	void ChangeFeverTimeState ( bool state );

	void GenerateNewGems();
	void TotalUpGems();

	void DrawComboGauge ();
	uchar GetRandGemID ( bool isAutoBalance = false );

	void ProcessSpecialGemEffect ( int x, int y, GEM_TYPE t = GEM_TYPE_UNKNOWN );
	void ProcessCandyGem ( GEM &g );
	void GenerateCandyGem ();

	COORD FindMostSwapableGem ();

	bool ProcessGameInputEvent();
	void Redraw( bool isForceRedraw = false );
	void InitialNewGame();
};


#endif

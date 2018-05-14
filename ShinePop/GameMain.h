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
	GEM_TYPE_FOUR = 2, // 四連続
	GEM_TYPE_FIVE = 3, // 五連続
	GEM_TYPE_CANDY = 4, // キャンディーブロック
};

typedef unsigned char uchar;

typedef struct _GEM {
	uchar id;    // 種類
	GEM_TYPE s;  // 特殊ブロック（４・５連続,etc）
	uchar hc;    // 横連続ブロック数
	uchar vc;    // 縦連続ブロック数
	bool del;    // 消せるブロックかどうか
	bool redraw; // 描き直す
	uchar bid;   // キャンディーブロック用のID（GEMのオブジェクトを作るべきだが）

	int yOffset; // アニメーション用
 
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

	// 各種ブロックの個数を集計用（ 個数 ）
	uchar gemStat[BOARD_GEM_COUNT];
	// 生成用確率テーブル
	uchar gemProbTable[BOARD_GEM_COUNT];

	unsigned long curTick;
	unsigned long feverEndTime;

	GEM _gems[BOARD_WIDTH][BOARD_HEIGHT];

	COORD pos[2]; //　最後に触ったブロックの位置
	
	unsigned long chgCols; // 影響した列、Bit Flags
	unsigned long chgRows; // 影響した行、Bit Flags
	unsigned long animCols; // アニメ演出する列

	int lastDelete; // アニメ演出用
	int scoreGaugeValue; // アニメ演出用

	SWAP_DIRECTION direct;

	// コンボ時間の履歴
	std::queue<unsigned long> comboLog;
	// コンボ数
	int comboCount;
	// コンボゲージの値
	int comboGaugeValue;
	// コンボゲージの最後変更時間
	unsigned long lastComboGaugeChanged;
	// 最後の交換時間
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

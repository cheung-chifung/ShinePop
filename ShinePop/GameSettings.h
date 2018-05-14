#pragma once

#ifndef GameSettings_H
#define GameSettings_H

/*
 * === GAME SETTINGS ===
 */
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 35

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 7
#define BOARD_GEM_COUNT 7

// 一回のゲームの時間、単位：ms
#ifdef _DEBUG
	#define GAME_TIME 90 * 1000
#else
	#define GAME_TIME 60 * 1000
#endif

#define GAME_TIME_WARNING_LINE 0.15f

// FeverTimeの長さ、単位：ms
#ifdef _DEBUG
	#define FEVER_TIME_DURATION 15 * 1000
#else
	#define FEVER_TIME_DURATION 8 * 1000
#endif

#define FEVER_TIME_WARNING_LINE FEVER_TIME_DURATION / 1000 * 0.15f

// FeverTimeに入るための時間基準
#ifdef _DEBUG
	#define FEVER_THRESHOLD_TIME 20 * 1000
#else
	#define FEVER_THRESHOLD_TIME 8 * 1000
#endif

// FeverTimeに入るためのコンボ基準
#ifdef _DEBUG
	#define FEVER_THRESHOLD_COMBO_COUNT 3
#else
	#define FEVER_THRESHOLD_COMBO_COUNT 5
#endif

// この時間内に交換できればコンボと見なす、単位：ms
#ifdef _DEBUG
	#define COMBO_THRESHOLD_TIME 10 * 1000
#else
	#define COMBO_THRESHOLD_TIME 3 * 1000
#endif

// ヒントが出る時間基準、単位：ms
#ifdef _DEBUG
	#define HINT_THRESHOLD_TIME 4 * 1000
#else
	#define HINT_THRESHOLD_TIME 2 * 1000
#endif

// コンボゲージの最大長さ
#ifdef _DEBUG
	#define COMBO_GAUGE_LEN 3
#else
	#define COMBO_GAUGE_LEN 5
#endif

/*
 * = コンボ・フィーバーの仕様説明
 *
 * > 一回消してCOMBO_THRESHOLD_TIME内に次のを消せばcomboゲージ+1、combo数+1
 * > 　　次のを消背なければcomboゲージ-1、combo数=0
 * > comboゲージがCOMBO_GAUGE_LENになったらランダムにキャンディーブロックを生成し、comboゲージ=0
 * > フィーバータイムの条件：FEVER_THRESHOLD_TIME内にFEVER_THRESHOLD_COMBO_COUNT回のcomboを達成できればフィーバータイムに入る
 * >     フィーバータイムはFEVER_TIME_DURATIONの長さで継続、その間にまたフィーバータイムの条件を達成できれば
 * >     その時点に新しいフィーバータイムに入る（延長）
 *
 */

#define RANKING_LENGTH 5
#endif
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

// ���̃Q�[���̎��ԁA�P�ʁFms
#ifdef _DEBUG
	#define GAME_TIME 90 * 1000
#else
	#define GAME_TIME 60 * 1000
#endif

#define GAME_TIME_WARNING_LINE 0.15f

// FeverTime�̒����A�P�ʁFms
#ifdef _DEBUG
	#define FEVER_TIME_DURATION 15 * 1000
#else
	#define FEVER_TIME_DURATION 8 * 1000
#endif

#define FEVER_TIME_WARNING_LINE FEVER_TIME_DURATION / 1000 * 0.15f

// FeverTime�ɓ��邽�߂̎��Ԋ
#ifdef _DEBUG
	#define FEVER_THRESHOLD_TIME 20 * 1000
#else
	#define FEVER_THRESHOLD_TIME 8 * 1000
#endif

// FeverTime�ɓ��邽�߂̃R���{�
#ifdef _DEBUG
	#define FEVER_THRESHOLD_COMBO_COUNT 3
#else
	#define FEVER_THRESHOLD_COMBO_COUNT 5
#endif

// ���̎��ԓ��Ɍ����ł���΃R���{�ƌ��Ȃ��A�P�ʁFms
#ifdef _DEBUG
	#define COMBO_THRESHOLD_TIME 10 * 1000
#else
	#define COMBO_THRESHOLD_TIME 3 * 1000
#endif

// �q���g���o�鎞�Ԋ�A�P�ʁFms
#ifdef _DEBUG
	#define HINT_THRESHOLD_TIME 4 * 1000
#else
	#define HINT_THRESHOLD_TIME 2 * 1000
#endif

// �R���{�Q�[�W�̍ő咷��
#ifdef _DEBUG
	#define COMBO_GAUGE_LEN 3
#else
	#define COMBO_GAUGE_LEN 5
#endif

/*
 * = �R���{�E�t�B�[�o�[�̎d�l����
 *
 * > ��������COMBO_THRESHOLD_TIME���Ɏ��̂�������combo�Q�[�W+1�Acombo��+1
 * > �@�@���̂����w�Ȃ����combo�Q�[�W-1�Acombo��=0
 * > combo�Q�[�W��COMBO_GAUGE_LEN�ɂȂ����烉���_���ɃL�����f�B�[�u���b�N�𐶐����Acombo�Q�[�W=0
 * > �t�B�[�o�[�^�C���̏����FFEVER_THRESHOLD_TIME����FEVER_THRESHOLD_COMBO_COUNT���combo��B���ł���΃t�B�[�o�[�^�C���ɓ���
 * >     �t�B�[�o�[�^�C����FEVER_TIME_DURATION�̒����Ōp���A���̊Ԃɂ܂��t�B�[�o�[�^�C���̏�����B���ł����
 * >     ���̎��_�ɐV�����t�B�[�o�[�^�C���ɓ���i�����j
 *
 */

#define RANKING_LENGTH 5
#endif
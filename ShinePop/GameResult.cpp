
#include "GameResult.h"
#include "GameManager.h"

GameResult::GameResult(void)
{
	im = im->Instance ();
	om = om->Instance ();

}

void GameResult::Start ()
{
	GameManager* gm;
	gm = gm->Instance ();
	INPUT_EVENT ie = im->GetInputEvent();

	LPCTSTR sk = TEXT("Software\\ShinePop");
	HKEY hk;
	DWORD dwDisp;
	DWORD value;
	std::list <DWORD> ranking = std::list <DWORD> ();
	std::list <DWORD>::iterator rankingIter;
	DWORD dwData;
	DWORD cbData = sizeof(DWORD);
	TCHAR keyName [5];
	int i;

	// ランキング履歴を読み込む
	RegCreateKeyEx ( HKEY_CURRENT_USER, sk, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk, &dwDisp );
	for ( i = 0; i < RANKING_LENGTH; i++ ) {
		wsprintf ( keyName, TEXT("S%03d"), i);
		if ( ERROR_SUCCESS == RegQueryValueEx ( hk, keyName, NULL, NULL, (LPBYTE)&dwData, &cbData ) ) {
			ranking.push_back ( dwData );
		} else {
			ranking.push_back ( 0 );
		}
	}

	// TODO should use binary tree ?
	ranking.push_back ( gm->score );
	ranking.sort ( std::greater<DWORD>() );

	// ランキング履歴を書き込む
	i = 0;
	rankingIter = ranking.begin();
	while ( i < RANKING_LENGTH ) {
		wsprintf ( keyName, TEXT("S%03d"), i );
		value = *rankingIter;
		RegSetValueEx ( hk, keyName, 0, REG_DWORD, (BYTE*)&value, sizeof(value) );
		i ++;
		rankingIter ++;
	}

	RegCloseKey ( hk );

	// タイトルの表示
	const unsigned char illumColor[7] = {
		COLOR_LIGHT_YELLOW, COLOR_LIGHT_YELLOW, COLOR_LIGHT_GREEN, COLOR_LIGHT_GREEN,
		COLOR_YELLOW, COLOR_YELLOW, COLOR_LIGHT_GREEN
	};
	const char illumText[7][80] = {
		" _______  ___   __   __  _______  __   _______    __   __  _______ \n",
		"|       ||   | |  |_|  ||       ||  | |       |  |  | |  ||       |\n",
		"|_     _||   | |       ||    ___||__| |  _____|  |  | |  ||    _  |\n",
		"  |   |  |   | |       ||   |___      | |_____   |  |_|  ||   |_| |\n",
		"  |   |  |   | |       ||    ___|     |_____  |  |       ||    ___|\n",
		"  |   |  |   | | ||_|| ||   |___       _____| |  |       ||   |    \n",
		"  |___|  |___| |_|   |_||_______|     |_______|  |_______||___|    \n"
	};
	
	int l = 6;

	int selOpt = 0; // 1 for retry ; 2 for exit
	const int optionCount = 2;

	om->Print( COLOR_WHITE, l, 22, "     YOUR SCORE             =        %10d\n", gm->score);
	om->Print( COLOR_GRAY, l, 14, "____________ ");
	om->Print( COLOR_WHITE, "RANK");
	om->Print( COLOR_GRAY, " _______________________ ");
	om->Print( COLOR_WHITE, "SCORE");
	om->Print( COLOR_GRAY, " _________________\n");
	i = 0;
	rankingIter = ranking.begin();
	bool listUserScore = false;

	while ( i < RANKING_LENGTH ) {
		om->GotoXY( l, 16 + i);
		
		if ( !listUserScore && *rankingIter == gm->score ) {
			listUserScore = true;
			om->Print( COLOR_LIGHT_RED, "            YOU                      ", i+1 );
		} else {
			om->Print( COLOR_GREEN,  "             %2d                      ", i+1 );
			om->SetColor ( COLOR_LIGHT_GREEN );
		}
		om->Print( "%10d                  \n", *rankingIter );
		i ++;
		rankingIter ++;
	}

	bool exit = false;
	int k = 0;
	while ( !exit ) {
		gm->BeginFrame ();
		int k = gm->GetFrameCount() / 5 ;
		for ( int i = 0; i < 7; i++ ) {
			om->Print ( illumColor[ (i + k) % 7 ], l, 4 + i, illumText[i] );
		}

		om->SetColor( selOpt == 1 ? COLOR_WHITE | BACKGROUND_RED : COLOR_LIGHT_GREEN );
		om->GotoXY(l, 26);
		om->Print("[                           RETRY                               ]\n");
		om->SetColor( selOpt == 2 ? COLOR_WHITE | BACKGROUND_RED : COLOR_LIGHT_GREEN );
		om->GotoXY(l, 28);
		om->Print("[                        BACK TO TITLE                          ]\n");

		// キー処理
		ie = im->GetInputEvent();
		if ( ie.keyPressed ) {
			if ( ie.key == KEY_UP ) {
				if (selOpt > 1) selOpt--;
			} else if ( ie.key == KEY_DOWN ) {
				if (selOpt < optionCount) selOpt++;
			} else if ( ie.key == KEY_ESCAPE ) {
				exit = true;
				break;
			} else if ( ie.key == KEY_ENTER || ie.key == KEY_SPACE ) {
				break;
			}
		} else if ( ie.mouseClicked ) {
			if ( ie.pos.Y == 26 ) {
				selOpt = 1;
				break;
			} else if ( ie.pos.Y == 28 ) {
				selOpt = 2;
				break;
			}
		}
		gm->EndFrame ();
	}

	if (selOpt == 1 && !exit ) gm->ChangeGameState ( GAME_STATE_MAIN );
	if (selOpt == 2 && !exit ) gm->ChangeGameState ( GAME_STATE_TITLE );

}


#include "GameTitle.h"
#include "GameManager.h"

GameTitle::GameTitle ()
{
	im = im->Instance ();
	om = om->Instance ();
}

void GameTitle::Start ()
{
	GameManager* gm;
	gm = gm->Instance ();

	INPUT_EVENT ie = im->GetInputEvent();

	// タイトルの表示
	int l = 6;

	int selOpt = 0; // 1 for new game; 2 for exit
	const int optionCount = 2;

	bool exit = false;

	const unsigned char illumColor[7] = {
		COLOR_LIGHT_YELLOW, COLOR_LIGHT_YELLOW, COLOR_LIGHT_YELLOW, COLOR_LIGHT_YELLOW,
		COLOR_GREEN, COLOR_GREEN, COLOR_LIGHT_YELLOW
	};
	const char illumText[7][80] = {
		" _______  __   __  ___   __    _  _______    _______  _______  _______ ",
		"|       ||  | |  ||   | |  |  | ||       |  |       ||       ||       |",
		"|  _____||  |_|  ||   | |   |_| ||    ___|  |    _  ||   _   ||    _  |",
		"| |_____ |       ||   | |       ||   |___   |   |_| ||  | |  ||   |_| |",
		"|_____  ||       ||   | |  _    ||    ___|  |    ___||  |_|  ||    ___|",
		" _____| ||   _   ||   | | | |   ||   |___   |   |    |       ||   |    ",
		"|_______||__| |__||___| |_|  |__||_______|  |___|    |_______||___|    "
	};

	while ( !exit ) {

		gm->BeginFrame ();

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

		int k = gm->GetFrameCount() / 10;
		for ( int i = 0; i < 7; i++ ) {
			om->Print ( illumColor[ (i + k) % 7 ], l - 2, 4 + i, illumText[i] );
		}
		om->SetColor ( selOpt == 1 ? COLOR_WHITE | BACKGROUND_RED : COLOR_LIGHT_GREEN );
		om->GotoXY ( l, 26 );
		om->Print( "[                          NEW GAME                              ]\n");
		om->SetColor( selOpt == 2 ? COLOR_WHITE | BACKGROUND_RED : COLOR_LIGHT_GREEN );
		om->GotoXY ( l, 28 );
		om->Print ( "[                            EXIT                                ]\n");

		om->Print( COLOR_GRAY, l, 13, "_________________________________________________________________\n");
		om->Print( COLOR_LIGHT_RED, l, 18, "                           By Cheung                             \n");

		gm->EndFrame();
	}
	if ( selOpt == 1 && !exit ) gm->ChangeGameState ( GAME_STATE_MAIN );
}
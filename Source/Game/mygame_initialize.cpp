#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;
int levelrank::value = -1;
int Step::step = 0;
int Score::score = 0;
CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
	
}
void CGameStateInit::OnInit()
{

}

void CGameStateInit::OnBeginState()
{
	level = levelrank::value;
	game_system.Ui.start_UI_init();
	game_system.Ui.rank_choose_UI();
	if ((phase_start == 2) && (phase_rank == 2)) {
		game_system.Ui.rank_choose_UI_2();
	}
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (phase_start == 1) {
		if (game_system.Ui.is_play_button(point)) {
			phase_start += 1;
		}
	}
	else if (phase_start == 2) {
		if (phase_rank == 1) {
			if (game_system.Ui.rank_down_button.isClick_CMovingBitmap(game_system.Ui.rank_down_button, point)) {
				game_system.Ui.rank_choose_UI_2();
				phase_rank += 1;
			}
			level = game_system.Ui.is_rank_button_1(point);
		}
		else if (phase_rank == 2) {
			if (game_system.Ui.rank_up_button.isClick_CMovingBitmap(game_system.Ui.rank_up_button, point)) {
				game_system.Ui.rank_choose_UI();
				phase_rank -= 1;
			}
			level = game_system.Ui.is_rank_button_2(point);
		}
	}
	if (level > -1) {
		levelrank::value = level; 
		GotoGameState(GAME_STATE_RUN);
	}
}

void CGameStateInit::OnShow()
{
	if (phase_start == 1) {
		game_system.Ui.start_loading.ShowBitmap();
	}
	else if ((phase_start == 2) && (phase_rank == 1)) {
		game_system.Ui.rankchoose_UI_show();
	}
	else if ((phase_start == 2) && (phase_rank == 2)) {
		game_system.Ui.rankchoose_UI_2_show();
	}
}
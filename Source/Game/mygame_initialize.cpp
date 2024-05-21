#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"


using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

int levelrank::value = -1;

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	//ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	//
	//開始載入資料
	//
	//Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//

}

void CGameStateInit::OnBeginState()
{
	StartUI.START_UI();
	
	RankChooseUI.Rank_choose_UI();
	if ((phase_start == 2) && (phase_rank == 2)) {
		RankChooseUI.Rank_choose_UI_2();
	}
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (phase_start == 1) {
		if (StartUI.IS_PLAY_BUTTON(point) == true) {
			phase_start += 1;
		}
	}
	else if ((phase_start == 2) && (phase_rank == 1)) {
		if (RankChooseUI.IS_DOWN_BUTTON(point) == true) {
			RankChooseUI.Rank_choose_UI_2();
			phase_rank += 1;
		}
		levelrank::value = RankChooseUI.IS_RANK_BUTTON_1(point);

	}
	else if ((phase_start == 2) && (phase_rank == 2)) {
		
		if (RankChooseUI.IS_UP_BUTTON(point) == true) {
			RankChooseUI.Rank_choose_UI();
			phase_rank -= 1;
		}
		levelrank::value = RankChooseUI.IS_RANK_BUTTON_2(point);

	}
	if (levelrank::value > -1) {
		GotoGameState(GAME_STATE_RUN);
	}

}

void CGameStateInit::OnShow()
{

	if (phase_start == 1) {
		StartUI.start_ui_show();

	}
	if ((phase_start == 2) && (phase_rank == 1)) {
		RankChooseUI.rankchoose_ui_show();
	}
	else if ((phase_start == 2) && (phase_rank == 2)) {
		RankChooseUI.rankchoose_ui_2_show();
	}
}
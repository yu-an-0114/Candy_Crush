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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

int levelrank::value = -1;

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	//ShowInitProgress(0, "Start Initialize...");	// �@�}�l��loading�i�׬�0%
	//
	//�}�l���J���
	//
	//Sleep(1000);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
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
	start_loading.LoadBitmapByString({ "resources/Start.bmp","resources/Start_loading.bmp","resources/Start_UI.bmp" }, RGB(255, 255, 255));
	start_loading.SetTopLeft(0, 0);
	start_loading.SetAnimation(1000, true);
	play.LoadBitmapByString({ "resources/play.bmp" });
	play.SetTopLeft(600,770);
}

void CGameStateInit::OnBeginState()
{
	
	start_loading.ToggleAnimation();
	
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((600 > point.x && point.x > 150) && (800>point.y &&point.y >640) && start_loading.GetFrameIndexOfBitmap()==2) {
		GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
	}
	
}

void CGameStateInit::OnShow()
{

	start_loading.ShowBitmap();
	//play.ShowBitmap();
	
		//phase_start += 1;
	

	//start_ui.ShowBitmap();
	//start_ui.ToggleAnimation();
	//OnBeginState();
}

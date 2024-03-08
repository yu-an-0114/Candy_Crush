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
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
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

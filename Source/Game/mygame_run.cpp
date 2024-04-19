#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cstdio>

#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"


using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{

	MAP.Candy_Element( clickX, clickY, changeX, changeY);
	MAP.candy_down();
	if (MAP.step == 10) {
		MAP.score = 0;
	}
	
	MAP.SCORE();
	MAP.STEP();
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	MAP.Build_map();
	UI.RUN();
	UI.RUN2();
	UI.Win();
	UI.Board_set();
	UI.Fail();
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	
	mouse_candy_state = true;
	candy_start = point;
	if (UI.IS_HOME(point) == true) {
		GotoGameState(GAME_STATE_INIT);
		MAP.step = 10;
		MAP.score = 0;
		MAP.Build_map();
		phase_run = 1;
	}
	if (UI.IS_SETTING(point) == true) {
		UI.RUN();
		phase_run += 1;
		phase_rank += 1;
	}
	/*
	if (UI.IS_RETRY(point) == true) {
		MAP.step = 10;
		MAP.score = 0;
		MAP.Build_map();
		phase_run -= 1;
	}*/
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	mouse_candy_state = false;

	if (num == 1 && mouse_candy_state ==false) {
		num = 0;
		int change = 0;
		for (int i = 0; i < 10; i++) {
			if (change == 1) {
				break;
			}
			for (int j = 0; j < 10; j++) {
				if (change == 1) {
					break;
				}
				if (MAP.map[i][j].isClick_CMovingBitmap(MAP.candy[i][j], point) && MAP.candy[i][j].GetFrameIndexOfBitmap()!=0 && MAP.candy[clickX][clickY].GetFrameIndexOfBitmap() != 0) {
					if ((clickX - 1 == i && clickY == j) || (clickX + 1 == i && clickY == j) || (clickX == i && clickY - 1 == j) || (clickX == i && clickY + 1 == j)) {
						change = 1;
						MAP.candy_change(i, j, clickX, clickY);
						changeX = clickX;
						changeY = clickY;
						clickX = i;
						clickY = j;	
						MAP.step = MAP.step - 1;
						
						break;
					}
					else {
						MAP.candy[clickX][clickY].SetTopLeft(MAP.map[clickX][clickY].GetLeft() + (MAP.map[clickX][clickY].GetWidth() - MAP.candy[clickX][clickY].GetWidth()) / 2, MAP.map[clickX][clickY].GetTop() + (MAP.map[clickX][clickY].GetHeight() - MAP.candy[clickX][clickY].GetHeight()) / 2);
					}
				}
				else if (i == 9 && j == 9) {
					MAP.candy[clickX][clickY].SetTopLeft(MAP.map[clickX][clickY].GetLeft() + (MAP.map[clickX][clickY].GetWidth() - MAP.candy[clickX][clickY].GetWidth()) / 2, MAP.map[clickX][clickY].GetTop() + (MAP.map[clickX][clickY].GetHeight() - MAP.candy[clickX][clickY].GetHeight()) / 2);
				}
			}
		}
		
	}
	if (UI.IS_HOME(point) == true) {
		GotoGameState(GAME_STATE_INIT);
		phase_run = 1;
	}
	if (UI.IS_SETTING(point) == true) {
		phase_run += 1;
	}
	if (UI.IS_RETRY(point) == true) {
		phase_run -= 1;
	}
	
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (mouse_candy_state == true && num == 0) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (MAP.candy[i][j].isClick_CMovingBitmap(MAP.candy[i][j], candy_start)) {
					num = 1;
					clickX = i;
					clickY = j;
					break;
				}
			}
		}
	}
	if (mouse_candy_state == true && num==1) {
		if (MAP.candy[clickX][clickY].isClick_CMovingBitmap(MAP.candy[clickX][clickY], candy_start)) {
			MAP.candy[clickX][clickY].SetTopLeft(point.x - MAP.candy[clickX][clickY].GetWidth() / 2, point.y - MAP.candy[clickX][clickY].GetHeight() / 2);
			candy_start = point;
		}
	}
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	MAP.Show_map();
	UI.Setting_Show();
	if (MAP.step == 0) {
		if (MAP.score < 300) {
			UI.Fail_ui_show();
		}
		else if (MAP.score < 500) {
			UI.win_ui_show(1);
		}
		else if (MAP.score < 1000) {
			UI.win_ui_show(2);
		}
		else {
			UI.win_ui_show(3);
		}
	}
	else {
		//Setting_UnShow()0
	}

	if ((phase_run == 2) && (phase_rank == 2)) {
		UI.Setting_RUN_show();
		//GotoGameState(GAME_STATE_INIT);
		//phase_run = 1;
	}
	else {
		UI.Setting_RUN_Unshow();
	}
	
}

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
	
	MAP.Candy_Element( clickX, clickY, changeX, changeY, level);
	MAP.candy_down(level);
	
	if (helper.IsnewGame(LevelCheck::rank, LevelCheck::step)) {
		LevelCheck::score = 0;
	}

	helper.SCORE();
	helper.STEP();
	time.Delay(50);
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	
	MAP.Build_map(level);
	UI.map_background(A);
	UI.RUN2();
	UI.Win();
	UI.Board_set();
	UI.Fail();
<<<<<<< HEAD
	UI.GoalSetting();
	//UI.GoalInit();
=======
>>>>>>> 5d04bc4d14e11385b18eee98749bbf73d2ed1a99

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	showEffect = false;
	canMove = true;
	mouse_candy_state = true;
	candy_start = point;
	
	if (UI.IS_SETTING(point) == true) {
		if ((phase_run == 1) && (phase_rank == 1)) {
			//UI.RUN();
			phase_run += 1;
			phase_rank += 1;
		}
		else if ((phase_run == 2) && (phase_rank == 2)) {
			phase_run -= 1;
			phase_rank -= 1;
		}
	}
	if (((phase_run == 2) && (phase_rank == 2)) || ((phase_run == 3) && (phase_rank == 3))) {
		if (UI.IS_HOME(point) == true) {
<<<<<<< HEAD
			LevelCheck::rank = -1;
=======
			levelrank::value = -1;
>>>>>>> 5d04bc4d14e11385b18eee98749bbf73d2ed1a99
			GotoGameState(GAME_STATE_INIT);
			
			MAP.Build_map(level);
			LevelCheck::step = helper.stepInit(LevelCheck::rank);
			LevelCheck::score = 0;
			phase_run = 1;
			phase_rank = 1;
		}

		if (UI.IS_RETRY(point) == true) {
			
			MAP.Build_map(level);
			LevelCheck::step = helper.stepInit(LevelCheck::rank);
			LevelCheck::score = 0;
			phase_run = 1;
			phase_rank = 1;
		}
		if (UI.IS_CLOSE(point) == true) {
			phase_run -= 1;
			phase_rank -= 1;
		}
		if (UI.IS_NEXT(point) == true) {
			LevelCheck::rank += 1;
			
			MAP.Build_map(level);

			LevelCheck::step = helper.stepInit(LevelCheck::rank);

			LevelCheck::score = 0;
			phase_run = 1;
			phase_rank = 1;
		}
	}
}
  

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	showEffect = true; 
	mouse_candy_state = false;
	
	if (num == 1 && mouse_candy_state ==false  && canMove == true) {
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
				if (MAP.maplevel.mapLevel[level][i][j] == 0) {
					continue;
				}
				
				if (MAP.map[i][j].isClick_CMovingBitmap(MAP.candy[i][j], point) && MAP.candy[i][j].GetFrameIndexOfBitmap()!=0 && MAP.candy[clickX][clickY].GetFrameIndexOfBitmap() != 0) {
					if ((clickX - 1 == i && clickY == j) || (clickX + 1 == i && clickY == j) || (clickX == i && clickY - 1 == j) || (clickX == i && clickY + 1 == j)) {
						change = 1;
						MAP.candy_change(i, j, clickX, clickY, level);
						changeX = clickX;
						changeY = clickY;
						clickX = i;
						clickY = j;	
						LevelCheck::step = helper.stepMove(LevelCheck::step);
						
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
<<<<<<< HEAD

=======
	
	
>>>>>>> 5d04bc4d14e11385b18eee98749bbf73d2ed1a99
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	
	if (mouse_candy_state == true && num == 0) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (MAP.maplevel.mapLevel[level][i][j] == 0) {
					continue;
				}
				if (MAP.candy[i][j].isClick_CMovingBitmap(MAP.candy[i][j], candy_start)) {
					num = 1;
					clickX = i;
					clickY = j;
					break;
				}
			}
		}
	}

	if (MAP.maplevel.mapLevel[LevelCheck::rank][clickX][clickY] == 1 && MAP.blocklevel.blockLevel[LevelCheck::rank][clickX][clickY] == 1) {
		canMove = false;
		return;
	}

	
	
	if (mouse_candy_state == true && num==1) {
		if (MAP.candy[clickX][clickY].isClick_CMovingBitmap(MAP.candy[clickX][clickY], candy_start)) {
			MAP.candy[clickX][clickY].SetTopLeft(point.x - MAP.candy[clickX][clickY].GetWidth() / 2, point.y - MAP.candy[clickX][clickY].GetHeight() / 2);
			candy_start = point;
		}
	}
	else {
		return;
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
<<<<<<< HEAD

	UI.map_show(LevelCheck::score, A);
	MAP.Show_map(LevelCheck::rank);
=======
	
	UI.map_show(MAP.score, A);
	MAP.Show_map(levelrank::value);
>>>>>>> 5d04bc4d14e11385b18eee98749bbf73d2ed1a99
	UI.Setting_Show();
	UI.GoalShow();
	if (LevelCheck::step == 0) {
		phase_run = 3;
		phase_rank = 3;
	}
	



	if ((phase_run == 3) && (phase_rank == 3)) {
		if (LevelCheck::score < 300) {
			UI.Fail_ui_show();
		}
		else if (LevelCheck::score < 500) {
			UI.win_ui_show(1);
		}
		else if (LevelCheck::score < 1000) {
			UI.win_ui_show(2);
		}
		else {
			UI.win_ui_show(3);
		}
	}
	else {
		if (showEffect) {
			MAP.Show_effect(LevelCheck::rank);
		}
	}

	if ((phase_run == 2) && (phase_rank == 2)) {
		UI.Setting_RUN_show();
		//GotoGameState(GAME_STATE_INIT);
		//phase_run = 1;
	}

	//helper.RANK();
	helper.SCORE();
	helper.STEP();
}

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
	level = levelrank::value;
	game_system.map.build_map(level);
	goal_helper.goalInit(level);
	Step::step = step_helper.stepInit(level);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	game_system.map.map_level_text(level);
	//game_system.Candy_Element(game_system.clickX, game_system.clickY, game_system.changeX, game_system.changeY, level);
	//game_system.candy_down(level);
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{

	game_system.Ui.background();
	score_system.score_strip();
	score_system.score_background_init(scoreStar_place);
	goal_helper.GoalSetting(levelrank::value);

	//game_system.Ui.win();
	//game_system.Ui.board_set();
	//game_system.Ui.fail();
	//game_system.Ui.GoalSetting(LevelCheck::rank);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	game_system.canMove = true;
	game_system.mouse_candy_state = true;
	game_system.candy_start = point;
	if (phase == -1) {
		if (game_system.Ui.IS_SETTING(point)) {
			phase = 0;
		}
	}
	else if (phase >= 0) {
		if (phase == 0) {
			if (game_system.Ui.IS_SETTING(point)) {
				phase = -1;
			}
			if (game_system.Ui.IS_CLOSE(point)) {
				phase = -1;
			}
		}
		else if (phase == 2) {
			if (game_system.Ui.IS_NEXT(point)) {
				phase = -1;
				level += 1;
				goal_helper.goalInit(level);
				Step::step = step_helper.stepInit(level);
				game_system.map.build_map(level);
			}
		}
		if (game_system.Ui.IS_RETRY(point)) {
			phase = -1;
			goal_helper.goalInit(level);
			Step::step = step_helper.stepInit(level);
			game_system.map.build_map(level);
		}
		if (game_system.Ui.IS_HOME(point)) {
			phase = -1;
			GotoGameState(GAME_STATE_INIT);
			//levelrank::value = -1;
		}
	}


}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{


	game_system.mouse_candy_state = false;

	if (game_system.num == 1 && game_system.mouse_candy_state == false && game_system.canMove == true) {
		game_system.num = 0;
		int change = 0;
		for (int i = 0; i < 10; i++) {
			if (change == 1) {
				break;
			}
			for (int j = 0; j < 10; j++) {
				if (change == 1) {
					break;
				}
				if (map_level[level][i][j] == 0) {
					continue;
				}

				if (game_system.map.candy_lattice[i][j].isClick_CMovingBitmap(game_system.map.candy[i][j], point) && game_system.map.candy[i][j].GetFrameIndexOfBitmap() != 0 && game_system.map.candy[game_system.clickX][game_system.clickY].GetFrameIndexOfBitmap() != 0) {
					if ((game_system.clickX - 1 == i && game_system.clickY == j) || (game_system.clickX + 1 == i && game_system.clickY == j) || (game_system.clickX == i && game_system.clickY - 1 == j) || (game_system.clickX == i && game_system.clickY + 1 == j)) {
						change = 1;
						game_system.candy_change(i, j, game_system.clickX, game_system.clickY, level);
						game_system.changeX = game_system.clickX;
						game_system.changeY = game_system.clickY;
						game_system.clickX = i;
						game_system.clickY = j;
						break;
					}
					else {
						game_system.map.set_candy_lattice_center(game_system.clickX, game_system.clickY, game_system.map.candy);
					}
				}
				else if (i == 9 && j == 9) {
					game_system.map.set_candy_lattice_center(game_system.clickX, game_system.clickY, game_system.map.candy);
				}
			}
		}

	}

	Step::step -= 1;
	


}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{

	if (game_system.mouse_candy_state == true && game_system.num == 0) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (map_level[level][i][j] == 0) {
					continue;
				}
				if (game_system.map.candy[i][j].isClick_CMovingBitmap(game_system.map.candy[i][j], game_system.candy_start)) {
					game_system.num = 1;
					game_system.clickX = i;
					game_system.clickY = j;
					break;
				}
			}
		}
	}





	if (game_system.mouse_candy_state == true && game_system.num == 1) {
		if (game_system.map.candy[game_system.clickX][game_system.clickY].isClick_CMovingBitmap(game_system.map.candy[game_system.clickX][game_system.clickY], game_system.candy_start)) {
			game_system.map.candy[game_system.clickX][game_system.clickY].SetTopLeft(point.x - game_system.map.candy[game_system.clickX][game_system.clickY].GetWidth() / 2, point.y - game_system.map.candy[game_system.clickX][game_system.clickY].GetHeight() / 2);
			game_system.candy_start = point;
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
	game_system.Ui.background_show();
	score_system.score_board_show(100,scoreStar_place);
	game_system.map.show_map(level);

	
	if ((phase == -1) | (phase == 0) ){
		score_system.scoreShow();
		step_helper.stepShow();
		goal_helper.goalShow(level);
		goal_helper.goalShow(0, 305, 65);
		goal_helper.goalShow(1, 405, 65);
		goal_helper.goalShow(2, 505, 65);
		goal_helper.TEST(level);
	}
	if (Step::step <= 0) {
		phase = 1;

	}

	game_system.Ui.condition_show(phase);
}

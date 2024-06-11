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
	int init_map_level[10][10];
	goal_helper.goalInit(level);
	Step::step = step_helper.stepInit(level);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			init_map_level[i][j] = game_system.get_map_level(level, i, j);
		}
	}
	game_system.map.build_map(level);
	for (int t = 0; t < 3; t++) {
		game_system.object_check_element(game_system.clickX, game_system.clickY, game_system.changeX, game_system.changeY, level);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (init_map_level[i][j] == 1 && (game_system.map.candy[i][j].GetFrameIndexOfBitmap() == 0) || game_system.map.candy[i][j].GetFrameIndexOfBitmap() > 6) {
					game_system.map.candy[i][j].set_candy_random(i, j, level, game_system.map.candy);
				}
				else if (init_map_level[i][j] == 2 && game_system.get_map_level(level, i, j) != 2) {
					game_system.set_map_level(level, i, j, 2);
				}
				else if (init_map_level[i][j] == 4 && game_system.map.candy[i][j].GetFrameIndexOfBitmap() == 0) {
					game_system.map.candy[i][j].set_candy_random(i, j, level, game_system.map.candy);
					game_system.set_map_level(level, i, j, 4);
				}
				else if ((6 <= init_map_level[i][j] && init_map_level[i][j] <= 11) && init_map_level[i][j] != game_system.get_map_level(level, i, j)) {
					game_system.set_map_level(level, i, j, init_map_level[i][j]);
				}
				else if ((12 <= init_map_level[i][j] && init_map_level[i][j] <= 13) && init_map_level[i][j] != game_system.get_map_level(level, i, j)) {
					game_system.set_map_level(level, i, j, init_map_level[i][j]);
					game_system.map.candy[i][j].set_candy_random(i, j, level, game_system.map.candy);
				}
			}
		}
	}
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	game_system.map_level_text(level);
	//game_system.Ui.step.step_text(level);
	//game_system.candy_num_text(level);
	
	if (game_system.Ui.step.use_step) {
		int old_map_level[10][10] ;
		if (game_system.Ui.step.use_step) {
			while (1) {
				bool out = true;
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						old_map_level[i][j] = game_system.map.candy[i][j].GetFrameIndexOfBitmap();
					}
				}
				game_system.object_check_element(game_system.clickX, game_system.clickY, game_system.changeX, game_system.changeY, level);
				game_system.object_down(level);
				game_system.check_cherry_element(level);
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						if (old_map_level[i][j] != game_system.map.candy[i][j].GetFrameIndexOfBitmap()) {
							out = false;
						}
					}
				}
				if (out) {
					game_system.Ui.step.use_step = false;
					break;
				}
			}					
		}
		
		if (!game_system.step_has_chocolate_destory) {
			game_system.chocolate_generate(level);
		}
		game_system.Ui.step.use_step = false;
		game_system.step_has_chocolate_destory = false;
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	game_system.Ui.background();
	score_system.score_strip();
	score_system.score_background_init(scoreStar_place);
	goal_helper.GoalSetting(levelrank::value);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	Score::score = Score::score + 10;
	showEffect = false;
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
				Score::score = 0;
			}
		}
		if (game_system.Ui.IS_RETRY(point)) {
			phase = -1;
			goal_helper.goalInit(level);
			Step::step = step_helper.stepInit(level);
			game_system.map.build_map(level);
			Score::score = 0;
		}
		if (game_system.Ui.IS_HOME(point)) {
			phase = -1;
			GotoGameState(GAME_STATE_INIT);
			Score::score = 0;
			Step::step = step_helper.stepInit(level);
			//levelrank::value = -1;
		}
		if (game_system.Ui.IS_DEBUG_MODE(point)) {
			phase = 3;
		}
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	showEffect = true;
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
				if (game_system.map.candy_lattice[i][j].isClick_CMovingBitmap(game_system.map.candy_lattice[i][j], point)) {
					if ((game_system.clickX - 1 == i && game_system.clickY == j) || (game_system.clickX + 1 == i && game_system.clickY == j) || (game_system.clickX == i && game_system.clickY - 1 == j) || (game_system.clickX == i && game_system.clickY + 1 == j)) {
						change = 1;
						game_system.Ui.step.step_update();
						game_system.map.bomb[0][0].bomb_step_update(level, game_system.map.bomb);
						game_system.object_change(game_system.clickX, game_system.clickY, i, j, level);	
						game_system.changeX = game_system.clickX;
						game_system.changeY = game_system.clickY;
						game_system.clickX = i;
						game_system.clickY = j;
						game_system.map.set_candy_lattice_center(game_system.clickX, game_system.clickY, level);
						game_system.map.set_candy_lattice_center(game_system.changeX, game_system.changeY, level);
						break;
					}
					else {
						game_system.map.set_candy_lattice_center(game_system.clickX, game_system.clickY, level);
					}
				}
				else if (i == 9 && j == 9) {
					game_system.map.set_candy_lattice_center(game_system.clickX, game_system.clickY, level);
				}
			}
		}
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (game_system.mouse_candy_state == true && game_system.num == 0) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (map_level[level][i][j] == 0) {
					continue;
				}
				if (game_system.map.candy_lattice[i][j].isClick_CMovingBitmap(game_system.map.candy_lattice[i][j], game_system.candy_start)) {
					game_system.num = 1;
					game_system.clickX = i;
					game_system.clickY = j;
					break;
				}
			}
		}
	}

	if (game_system.mouse_candy_state == true && game_system.num == 1) {
		if (map_level[level][game_system.clickX][game_system.clickY] == 1 || map_level[level][game_system.clickX][game_system.clickY] == 12 || map_level[level][game_system.clickX][game_system.clickY] == 13) {
			if (oblect_click_mouse(game_system.map.candy)) {
				object_move_with_mouse(game_system.map.candy,point);
				game_system.candy_start = point;
			}
		}
		else if (map_level[level][game_system.clickX][game_system.clickY] == 3) {
			if (oblect_click_mouse(game_system.map.cherry)) {
				object_move_with_mouse(game_system.map.cherry,point);
				game_system.candy_start = point;
			}
		}
		else if (map_level[level][game_system.clickX][game_system.clickY] == 4) {
			if (oblect_click_mouse(game_system.map.bomb)) {
				object_move_with_mouse(game_system.map.bomb,point);
				game_system.candy_start = point;
			}
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
	starNum = score_system.score_board_show(Score::score, scoreStar_place);
	game_system.map.show_map(level);


	if ((phase == -1) | (phase == 0)) {
		score_system.scoreShow();
		step_helper.stepShow();
		goal_helper.goalShow(level);
		goal_helper.goalShow(0, 305, 65);
		goal_helper.goalShow(1, 405, 65);
		goal_helper.goalShow(2, 505, 65);
		goal_helper.TEST(level);
	}
	if (Step::step <= 0) {
		if (starNum > 0) {
			phase = 2;
		}
		else {
			phase = 1;
		}

	}

	if (phase == 3) {
		phase = 2;
	}
	game_system.Ui.condition_show(phase);

	game_system.map.bomb[0][0].bomb_step_text(level, game_system.map.bomb);

	if (showEffect) {
		game_system.map.Show_effect(levelrank::value);
	}
}

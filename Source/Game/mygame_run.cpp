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

int Step::step = 0;
int level= levelrank::value;
CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	level = levelrank::value;
	game_system.game_init(level);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	game_system.map_level_text(level);
	if (game_system.Step.use_step) {
		
		int old_map_level[10][10] ;

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

				break;
			}
		}
		if (!game_system.Ui.debug_mode) {
			game_system.map.Bomb.bomb_step_update(level, game_system.map.bomb);
		}


		if (!game_system.step_has_chocolate_destory) {
			game_system.chocolate_generate(level);
		}
		game_system.Step.use_step = false;
		game_system.step_has_chocolate_destory = false;
		
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	game_system.Ui.background();
	game_system.Score.score_strip();
	game_system.Score.score_background_init(scoreStar_place);
	game_system.effectlevel.effectLoad();
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
	showEffect = false;
	if (phase == -1) {
		if (game_system.Ui.IS_SETTING(point)) {
			phase = 0;
		}
	}
	else if (phase >= 0) {
		if ((phase == 0) || (phase == 3)) {
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

				game_system.Goal.goalInit(level);
				Step::step = game_system.Step.stepInit(level);
				game_system.map.build_map(level);
				Score::score = 0;
			}
		}
		if (game_system.Ui.IS_RETRY(point)) {
			phase = -1;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					map_level[level][i][j]=game_system.pre_map_level[i][j];
				}
			}
			game_system.Goal.goalInit(levelrank::value);
			Step::step = game_system.Step.stepInit(levelrank::value);

			game_system.game_init(level);
			
		}
		if (game_system.Ui.IS_HOME(point)) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					map_level[level][i][j] = game_system.pre_map_level[i][j];
				}
			}
			phase = -1;
			GotoGameState(GAME_STATE_INIT);
			Score::score = 0;
			Step::step = game_system.Step.stepInit(level);
			levelrank::value = -1;
		}
		if (game_system.Ui.IS_DEBUG_MODE(point)) {

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
					if ((( (game_system.clickX - 1 == i && game_system.clickY == j) || (game_system.clickX + 1 == i && game_system.clickY == j) || (game_system.clickX == i && game_system.clickY - 1 == j ) || (game_system.clickX == i && game_system.clickY + 1 == j ) )&& (game_system.can_change(i, j, game_system.clickX, game_system.clickY, level) || game_system.can_change(game_system.clickX, game_system.clickY,i,j, level)) || game_system.Ui.debug_mode)) {
						change = 1;
						game_system.object_change(game_system.clickX, game_system.clickY, i, j, level);
						game_system.Step.use_step = true;
						game_system.changeX = game_system.clickX;
						game_system.changeY = game_system.clickY;
						game_system.clickX = i;
						game_system.clickY = j;
						game_system.map.set_candy_lattice_center(game_system.clickX, game_system.clickY, level);
						game_system.map.set_candy_lattice_center(game_system.changeX, game_system.changeY, level);
						if (!game_system.Ui.debug_mode) {
							game_system.Step.step_update();
							game_system.color_ball(level);
						}
						
						break;
					}
					else {
						game_system.map.set_candy_lattice_center(game_system.clickX, game_system.clickY, level);
					}
				}
				else{
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
	if (game_system.Ui.debug_mode) {
		game_system.Ui.DEBUG_SHOW();
	}
	else {
		game_system.Ui.background_show();
		starNum = game_system.Score.score_board_show(Score::score, scoreStar_place);
	}

	game_system.map.show_map(level);
	if ((phase == -1) || (phase == 0)) {
		game_system.Score.scoreShow();
		game_system.Step.stepShow();
		game_system.Goal.goalShow(level);
	}

	if (game_system.Goal.Pass()) {
		pass = true;
		if (level < 5) {
			if (starNum == 3) {
				pass = true;
			}
			else {
				pass = false;
			}
		}
	}
	else {
		pass = false;
	}

	if (pass) {
		game_system.canMove = true;
		Step::step -= 1;
		Score::score += 1000;
		time.Delay(100);
	}

	game_system.map.Bomb.bomb_step_text(level, game_system.map.bomb);
	if (game_system.map.Bomb.IsBombZero(level, game_system.map.bomb)) {
		phase = 1;
	}
	if ((Step::step <= 0) && (pass)){
		game_system.canMove = false;
		if (starNum > 0) {
			phase = 2;
		}
		else {
			phase = 1;
		}

	}
	else if((Step::step <= 0) && (!pass)) {
		phase = 1;
	}
	game_system.Ui.condition_show(phase,starNum);
	if (showEffect) {
		game_system.effectlevel.Show_effect();

	}	
}

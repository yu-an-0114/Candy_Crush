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
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	game_system.map_level_text(level);
	//game_system.candy_num_text(level);
	//game_system.Candy_Element(game_system.clickX, game_system.clickY, game_system.changeX, game_system.changeY, level);
	//game_system.object_down(level);
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{

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
				if (game_system.map.candy_lattice[i][j].isClick_CMovingBitmap(game_system.map.candy_lattice[i][j], point)) {
					if ((game_system.clickX - 1 == i && game_system.clickY == j) || (game_system.clickX + 1 == i && game_system.clickY == j) || (game_system.clickX == i && game_system.clickY - 1 == j) || (game_system.clickX == i && game_system.clickY + 1 == j)) {
						change = 1;
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
	game_system.map.show_map(level);
}

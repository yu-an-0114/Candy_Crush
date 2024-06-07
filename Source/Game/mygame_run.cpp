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
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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

void CGameStateRun::OnMove()							// ���ʹC������
{
	game_system.map.map_level_text(level);
	//game_system.Candy_Element(game_system.clickX, game_system.clickY, game_system.changeX, game_system.changeY, level);
	//game_system.candy_down(level);
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	game_system.canMove = true;
	game_system.mouse_candy_state = true;
	game_system.candy_start = point;
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
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
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
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

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	game_system.map.show_map(level);
}

#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>


using namespace std;
namespace game_framework {
	class Bomb : public CMovingBitmap {
	public:
		void set_bomb_random(int x, int y, int level, Bomb bomb[10][10]) {
			int RandNum = rand() % 6 + 1;
			bomb[x][y].SetFrameIndexOfBitmap(RandNum);
			map_level[level][x][y] = 4;
		}
		void set_bomb_step(int x, int y, Bomb bomb[10][10], int step_num) {
			bomb_step[x][y] = step_num;
		}
		void bomb_init(int level, Bomb bomb[10][10]) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 4) {
						set_bomb_step(i,j,bomb,20);
					}
				}
			}
		}
		int get_bomb_step(int x, int y, Bomb bomb[10][10]) {
			return bomb_step[x][y];
		}
		void bomb_step_text(int level, Bomb bomb[10][10]) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 10, "Futura", RGB(0, 0, 0));
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 4) {
						CTextDraw::Print(pDC, bomb[i][j].GetLeft() + 13, bomb[i][j].GetTop() + 34, to_string(bomb_step[i][j]));
					}
				}
			}
			CDDraw::ReleaseBackCDC();
		}
		void bomb_step_update(int level, Bomb bomb[10][10]) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 4) {
						bomb_step[i][j]--;
					}
					else {
						bomb_step[i][j] = 0;
					}
				}
			}
		}
		bool is_bomb(int x, int y, int level) {
			return map_level[level][x][y] == 4;
		}
		bool IsBombZero(int level, Bomb bomb[10][10]) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 4) {
						if (bomb_step[i][j] < 1) {
							return true;
						}
					}
				}
			}
			return false;
		}
		int bomb_step[10][10] = {
			{20,20,20,20,20,20,20,20,20,20},
			{20,20,20,20,20,20,20,20,20,20},
			{20,20,20,20,20,20,20,20,20,20},
			{20,20,20,20,20,20,20,20,20,20},
			{20,20,20,20,20,20,20,20,20,20},
			{20,20,20,20,20,20,20,20,20,20},
			{20,20,20,20,20,20,20,20,20,20},
			{20,20,20,20,20,20,20,20,20,20},
			{20,20,20,20,20,20,20,20,20,20},
			{20,20,20,20,20,20,20,20,20,20} };
	};
}
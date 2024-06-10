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


using namespace std;
namespace game_framework {
	class Bomb : public CMovingBitmap {
	public:
		void set_bomb_random(int x, int y, int level, Bomb bomb[10][10]) {
			int RandNum = rand() % 6 + 1;
			bomb[x][y].SetFrameIndexOfBitmap(RandNum);
			map_level[level][x][y] = 4;
		}
		void bomb_step_text(int level, Bomb bomb[10][10]) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 10, "·L³n¥¿¶ÂÅé", RGB(0, 0, 0));
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 4) {
						CTextDraw::Print(pDC, bomb[i][j].GetLeft() +13, bomb[i][j].GetTop() + 34, to_string(bomb_step));
					}
				}
			}
			CDDraw::ReleaseBackCDC();
		}
		void bomb_step_update(int level, Bomb bomb[10][10]) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 4) {
						bomb_step--;
					}
				}
			}
		}
		int bomb_step = 20;
	private:

	};
}
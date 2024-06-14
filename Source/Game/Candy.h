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
	class Candy : public CMovingBitmap {
	public:


		bool is_candy(int x, int y, int level, Candy candy[10][10]) {
			if (map_level[level][x][y] == 1 && candy[x][y].GetFrameIndexOfBitmap() != 0) {
				return true;
			}
			return false;
		}
		bool is_candy_pack(int x, int y, Candy candy[10][10]) {
			if (is_color_ball(x, y, candy) || candy[x][y].GetFrameIndexOfBitmap() <= 6) {
				return false;
			}
			return (candy[x][y].GetFrameIndexOfBitmap() - 6) % 3 == 0;
		}
		bool is_candy_row(int x, int y, Candy candy[10][10]) {
			if (is_color_ball(x, y, candy) || candy[x][y].GetFrameIndexOfBitmap() <= 6) {
				return false;
			}
			return (candy[x][y].GetFrameIndexOfBitmap() - 6) % 3 == 1;
		}
		bool is_candy_col(int x, int y, Candy candy[10][10]) {
			if (is_color_ball(x, y, candy) || candy[x][y].GetFrameIndexOfBitmap() <= 6) {
				return false;
			}
			return (candy[x][y].GetFrameIndexOfBitmap() - 6) % 3 == 2;
		}
		bool is_color_ball(int x, int y, Candy candy[10][10]) {
			return candy[x][y].GetFrameIndexOfBitmap() == 25;
		}
		bool is_special_candy(int x, int y, Candy candy[10][10]) {
			return candy[x][y].GetFrameIndexOfBitmap() >25;
		}
		void set_candy_random(int x, int y, Candy candy[10][10]) {
			int RandNum = rand() % 6 + 1;
			candy[x][y].SetFrameIndexOfBitmap(RandNum);
		}
		void candy_upgrade(int x, int y, int type, Candy candy[10][10]) {
			candy[x][y].SetFrameIndexOfBitmap(type);
		}
	private:

	};
}
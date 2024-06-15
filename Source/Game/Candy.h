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
		bool is_candy_empty(int level, int x, int y, Candy candy[10][10]) {
			if (map_level[level][x][y] == 1 && candy[x][y].GetFrameIndexOfBitmap() == 0) {
				return true;
			}
			return false;
		}
		void set_candy_random(int x, int y, int level, Candy candy[10][10]) {
			int RandNum = rand() % 6 + 1;
			candy[x][y].SetFrameIndexOfBitmap(RandNum);
		}
	private:
		
	};
}
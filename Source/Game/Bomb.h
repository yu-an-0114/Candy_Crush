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

	private:

	};
}
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
	class X_block : public CMovingBitmap {
	public:
		void x_block_element(int x, int y, int level) {
			map_level[level][x][y] = 1;
		}
		bool is_x_block(int x, int y, int level) {
			return map_level[level][x][y] == 2;
		}

	private:

	};
}
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
	class Sugar : public CMovingBitmap {
	public:
		bool is_sugar(int x, int y, int level) {
			return 7 <= map_level[level][x][y] && map_level[level][x][y] <= 11;
		}

	private:

	};
}
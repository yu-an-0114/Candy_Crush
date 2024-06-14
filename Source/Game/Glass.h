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
	class Glass : public CMovingBitmap {
	public:
		bool is_glass(int x, int y, int level) {
			return 12 <= map_level[level][x][y] && map_level[level][x][y] <= 13;
		}
		void glass_element(int x, int y, int level) {
			if (map_level[level][x][y] == 12) {
				map_level[level][x][y] =  1;
			}
			if (map_level[level][x][y] == 13) {
				map_level[level][x][y] = 12;
			}
		}
	private:

	};
}
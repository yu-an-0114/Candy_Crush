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
	class ChocolateMachine : public CMovingBitmap {
	public:
		bool is_chocolate_machine(int x, int y, int level) {
			return map_level[level][x][y] == 5;
		}

	private:

	};
}
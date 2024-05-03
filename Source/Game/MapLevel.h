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
	class MapLevel {
	public:
		int mapLevel[2][10][10] = {//1
						   {{1,0,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1}},
							//2
						   {{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1}}

		};
	};
}

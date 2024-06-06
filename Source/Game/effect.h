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
	class Effect {
	public:
		int effect[10][10] = //1
		{ {0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,0,0,0,0,0,0} };

		void start() {

		}

		void shine(int X, int Y, int i = 1) {
			effect[X][Y] = i;
		}
		
		void Unshine(int X, int Y) {
			effect[X][Y] = 0;
		}
	};
}

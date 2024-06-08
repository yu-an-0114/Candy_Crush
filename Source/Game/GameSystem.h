//#ifdef MAP_H
//#define MAP_H
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
#include <typeinfo>
#include "Map.h"
#include "UI.h"
using namespace std;

namespace game_framework {
	class GameSystem {
	public:
		Map map;
		UI Ui;
	};
}


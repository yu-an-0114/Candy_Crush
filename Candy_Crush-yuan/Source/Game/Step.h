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
	class Step {
	public:
		static int step;
		Step() {

		}
		bool  use_step = false;

		void step_update() {
			use_step = true;
			step--;
		}
		int rankstep[30] = { 20, 20, 20, 20, 30,
							 20, 20, 20, 20, 30,
							 20, 20, 20, 20, 30,
							 20, 20, 20, 20, 30,
							 20, 20, 20, 20, 30,
							 40, 40, 40, 40, 40 };
		int stepInit(int level) {
			return rankstep[level];
		}


		bool IsNewGame(int level, int stepNow) {
			return stepNow == rankstep[level];
		}
		void stepShow() {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "¡PL?n??????", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 20, 90, "Step:" + to_string(step));
			CDDraw::ReleaseBackCDC();
		}
	};
}
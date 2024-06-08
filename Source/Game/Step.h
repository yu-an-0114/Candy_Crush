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

		int rankstep[20] = { 20, 20, 20, 20, 10,
							 10, 10, 10, 10, 10,
							 10, 10, 10, 10, 10,
							 10, 10, 10, 10, 10, };
		int stepInit(int level) {
			return rankstep[level];
		}

		int stepMove(int step) {
			return step - 1;
		}
		bool IsNewGame(int level, int stepNow) {
			return stepNow == rankstep[level];
		}
		void stepShow() {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "·L³n¥¿¶ÂÅé", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 20, 90, "Step:" + to_string(step));
			CDDraw::ReleaseBackCDC();
		}
	};
}
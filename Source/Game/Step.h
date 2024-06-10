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
	class Step  {
	public:
		void step_text(int level) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 10, "·L³n¥¿¶ÂÅé", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 20, 15, to_string(step));
			CDDraw::ReleaseBackCDC();
		}
		void step_update() {
			use_step = true;
			step--;
		}
		bool  use_step = false;
		int step=30;		
	};
}
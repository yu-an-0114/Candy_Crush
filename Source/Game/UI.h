
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

namespace game_framework {
	class UI{
	public:
		
		void START_UI() {
			start_loading.LoadBitmapByString({ "resources/Start.bmp","resources/Start_loading.bmp","resources/Start_UI.bmp" }, RGB(255, 255, 255));
			start_loading.SetTopLeft(0, 0);
			start_loading.SetAnimation(1000, true);
			play.LoadBitmapByString({ "resources/play.bmp" });
			play.SetTopLeft(600, 770);
			start_loading.ToggleAnimation();
		}
		void start_ui_show() {
			start_loading.ShowBitmap();	
		}
		bool IS_PLAY_BUTTON(CPoint point) {

				return (600 > point.x && point.x > 150) && (800 > point.y && point.y > 640) && start_loading.GetFrameIndexOfBitmap() == 2;
			
		}
	
	private:
		int phase_start = 1;
		CMovingBitmap play;								// csieªºlogo
		CMovingBitmap start_loading;
		CMovingBitmap start_ui;
	};
}



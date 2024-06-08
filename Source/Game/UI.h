
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <list>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include "Score.h"
#include "Step.h"
#include "Goal.h"
using namespace std;

namespace game_framework {
	class UI {
	public:
		void start_UI_init() {
			start_loading.LoadBitmapByString({ "resources/UI/Start.bmp","resources/UI/Start_loading.bmp","resources/UI/Start_UI.bmp" }, RGB(255, 255, 255));
			start_loading.SetTopLeft(0, 0);
			start_loading.SetAnimation(1000, true);
			start_loading.ToggleAnimation();
		}
		void rank_choose_UI() {

			rank_choose_map.LoadBitmapByString({ "resources/UI/map_level2.bmp" });
			rank_choose_map.SetTopLeft(0, -30);
			rank_down_button.LoadBitmapByString({ "resources/UI/arrow.bmp" }, RGB(255, 255, 255));
			rank_down_button.SetTopLeft(275, 875);

			for (int i = 0; i < 30; i++) {
				rank[i].LoadBitmapByString({ "resources/rank_bmp/rank_" + std::to_string(i + 1) + ".bmp" }, RGB(255, 255, 255));
			}
			for (int i = 0; i < 20; i++) {

				if (i < 5) {
					rank[i].SetTopLeft(30 + 115 * (i), 120);
				}
				else if (i < 10) {
					rank[i].SetTopLeft(30 + 115 * (i - 5), 250);
				}
				else if (i < 15) {
					rank[i].SetTopLeft(30 + 115 * (i - 10), 650);
				}
				else if (i < 20) {
					rank[i].SetTopLeft(30 + 115 * (i - 15), 780);
				}
			}

		}
		void rank_choose_UI_2() {
			rank_choose_map.SetTopLeft(0, -600);
			rank_up_button.LoadBitmapByString({ "resources/UI/up.bmp" }, RGB(255, 255, 255));
			rank_up_button.SetTopLeft(300, 0);
			for (int i = 10; i < 30; i++) {
				if (i < 15) {
					rank[i].SetTopLeft(30 + 115 * (i - 10), 120);
				}
				else if (i < 20) {
					rank[i].SetTopLeft(30 + 115 * (i - 15), 250);
				}
				else if (i < 25) {
					rank[i].SetTopLeft(30 + 115 * (i - 20), 650);
				}
				else if (i < 30) {
					rank[i].SetTopLeft(30 + 115 * (i - 25), 780);
				}
			}
		}
		void rankchoose_UI_show() {
			rank_choose_map.ShowBitmap();
			rank_down_button.ShowBitmap();
			for (int i = 0; i < 20; i++) {
				rank[i].ShowBitmap();
			}
		}

		void rankchoose_UI_2_show() {
			rank_choose_map.ShowBitmap();
			rank_up_button.ShowBitmap();

			for (int i = 10; i < 30; i++) {
				rank[i].ShowBitmap();
			}
		}

		void background() {
			game_background.LoadBitmapByString({ "resources/score/game_background.bmp" });
			game_background.SetTopLeft(0, -30);
			setting.LoadBitmapByString({ "resources/UI/set.bmp" }, RGB(255, 255, 255));
			setting.SetTopLeft(0, 0);
			board_set();
			fail();
			win();
		}
		void background_show() {
			game_background.ShowBitmap();
		}
		void condition_show(int phase) {
			setting_show();
			if (phase == 0) {
				Setting_RUN_show();
			}
			else if (phase == 1) {
				Fail_ui_show();
			}
			else if (phase == 2) {
				win_UI_show(1);
			}
		}


		void win() {
			win_background.LoadBitmapByString({ "resources/score/win_background.bmp" });
			win_background.SetTopLeft(0, -30);
			win_bird.LoadBitmapByString({ "resources/score/win_bird.bmp" }, RGB(255, 255, 255));
			win_bird.SetTopLeft(0, 700);
		}

		void fail() {
			fail_background.LoadBitmapByString({ "resources/score/lose_background.bmp" });
			fail_background.SetTopLeft(0, -100);
			fail_character.LoadBitmapByString({ "resources/score/lose_Character.bmp" }, RGB(255, 255, 255));
			fail_character.SetTopLeft(0, 700);
		}

		void board_set() {
			board.LoadBitmapByString({ "resources/score/board.bmp" }, RGB(255, 255, 255));
			board.SetTopLeft(125, 150);
			close.LoadBitmapByString({ "resources/score/close.bmp" }, RGB(255, 255, 255));
			close.SetTopLeft(board.GetLeft() + board.GetWidth() - 110, board.GetTop() + 80);
			star.LoadBitmapByString({ "resources/score/0star.bmp","resources/score/1star.bmp","resources/score/2stars.bmp","resources/score/3stars.bmp" }, RGB(255, 255, 255));
			star.SetTopLeft(board.GetLeft(), board.GetTop() + 200);
			star.SetAnimation(1000, true);
			retry.LoadBitmapByString({ "resources/score/Retry.bmp" }, RGB(255, 255, 255));
			retry.SetTopLeft(board.GetLeft() + 40, board.GetTop() + board.GetHeight() - 200);
			home.LoadBitmapByString({ "resources/score/home.bmp" }, RGB(255, 255, 255));
			home.SetTopLeft(retry.GetLeft() + retry.GetWidth(), retry.GetTop());
			next.LoadBitmapByString({ "resources/score/next.bmp" }, RGB(255, 255, 255));
			next.SetTopLeft(home.GetLeft() + home.GetWidth(), home.GetTop());
		}

		void win_UI_show(int x) {
			win_background.ShowBitmap();
			board.ShowBitmap();
			if (x == 1) {
				star.SetFrameIndexOfBitmap(1);
			}
			if (x == 2) {
				star.SetFrameIndexOfBitmap(2);
			}
			if (x == 3) {
				star.SetFrameIndexOfBitmap(3);
			}
			star.ShowBitmap();
			next.ShowBitmap();
			win_bird.ShowBitmap();
			retry.ShowBitmap();
			home.ShowBitmap();
		}

		void setting_show() {
			setting.ShowBitmap();
		}

		void Setting_RUN_show() {
			board.ShowBitmap();
			close.ShowBitmap();
			retry.ShowBitmap();
			home.ShowBitmap();
		}


		void Fail_ui_show() {
			fail_background.ShowBitmap();
			board.ShowBitmap();
			star.SetFrameIndexOfBitmap(0);
			star.ShowBitmap();
			fail_character.ShowBitmap();
			retry.ShowBitmap();
			home.ShowBitmap();
		}

		int is_rank_button_1(CPoint point) {
			for (int i = 0; i < 20; i++) {
				if (rank[i].isClick_CMovingBitmap(rank[i], point)) {
					return i;
				}
			}
			return -1;
		}
		int is_rank_button_2(CPoint point) {
			for (int i = 10; i < 30; i++) {
				if (rank[i].isClick_CMovingBitmap(rank[i], point)) {
					return i;
				}
			}
			return -1;
		}
		bool IS_SETTING(CPoint point) {
			return setting.isClick_CMovingBitmap(setting, point);
		}
		bool IS_CLOSE(CPoint point) {
			return close.isClick_CMovingBitmap(close, point);
		}
		bool is_play_button(CPoint point) {
			return (600 > point.x && point.x > 150) && (800 > point.y && point.y > 640) && start_loading.GetFrameIndexOfBitmap() == 2;
		}

		bool IS_NEXT(CPoint point) {
			return next.isClick_CMovingBitmap(next, point);
		}

		bool IS_RETRY(CPoint point) {
			return retry.isClick_CMovingBitmap(retry, point);
		}

		bool IS_HOME(CPoint point) {
			return home.isClick_CMovingBitmap(home, point);
		}
		CMovingBitmap start_loading;
		CMovingBitmap start_UI;
		CMovingBitmap rank_choose_map;
		CMovingBitmap rank_down_button;
		CMovingBitmap rank_up_button;
		CMovingBitmap rank[30];
		CMovingBitmap win_bird;
		CMovingBitmap game_background;
		CMovingBitmap win_background;
		CMovingBitmap fail_background;
		CMovingBitmap fail_character;
		CMovingBitmap board;
		CMovingBitmap star;
		CMovingBitmap retry;
		CMovingBitmap next;
		CMovingBitmap home;
		CMovingBitmap setting;
		CMovingBitmap close;
		Step step;
		Score score;
	};
}
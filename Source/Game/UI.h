
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <list>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

namespace game_framework {
	class UI {
	public:

		void START_UI() {
			start_loading.LoadBitmapByString({ "resources/Start.bmp","resources/Start_loading.bmp","resources/Start_UI.bmp" }, RGB(255, 255, 255));
			start_loading.SetTopLeft(0, 0);
			start_loading.SetAnimation(1000, true);
			start_loading.ToggleAnimation();
		}
		void Rank_choose_UI() {

			rank_choose_map.LoadBitmapByString({ "resources/map_level2.bmp" });
			rank_choose_map.SetTopLeft(0, -30);
			rank_down_button.LoadBitmapByString({ "resources/arrow.bmp" }, RGB(255, 255, 255));
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


		void Rank_choose_UI_2() {
			rank_choose_map.SetTopLeft(0, -600);
			rank_up_button.LoadBitmapByString({ "resources/up.bmp" }, RGB(255, 255, 255));
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
		void map_background(int *place) {
			Game_background.LoadBitmapByString({ "resources/score/game_background.bmp" });
			Game_background.SetTopLeft(0, -30);
			score_board.LoadBitmapByString({ "resources/score/score_board2.bmp" }, RGB(255, 255, 255));
			score_board.SetTopLeft(-20, 0);
			Point();
			score_star.LoadBitmapByString({ "resources/score/unlight_star.bmp","resources/score/light_star.bmp" }, RGB(255, 255, 255));
			score_star.SetTopLeft(point[place[0]].GetLeft(), point[28].GetTop() - 5);
			score_star.SetFrameIndexOfBitmap(0);
			score_star_2.LoadBitmapByString({ "resources/score/unlight_star.bmp","resources/score/light_star.bmp" }, RGB(255, 255, 255));
			score_star_2.SetTopLeft(point[place[1]].GetLeft(), point[61].GetTop() - 5);
			score_star_2.SetFrameIndexOfBitmap(0);
			score_star_3.LoadBitmapByString({ "resources/score/unlight_star.bmp","resources/score/light_star.bmp" }, RGB(255, 255, 255));
			score_star_3.SetTopLeft(point[95].GetLeft(), point[95].GetTop() - 5);
			score_star_3.SetFrameIndexOfBitmap(0);
			Setting.LoadBitmapByString({ "resources/set.bmp" }, RGB(255, 255, 255));
			Setting.SetTopLeft(0, 0);

		}
		void map_show(int score, int *place, int goal = 1000) {
			Game_background.ShowBitmap();
			score_board.ShowBitmap();

			goal = 500;
			int percentage = (score * 100 / goal);
			score_star.ShowBitmap();
			score_star_2.ShowBitmap();
			score_star_3.ShowBitmap();
			score_star.SetFrameIndexOfBitmap(0);
			score_star_2.SetFrameIndexOfBitmap(0);
			score_star_3.SetFrameIndexOfBitmap(0);
			for (int i = 1; i < percentage; i++) {

				if (i == 101) {
					break;
				}

				score_star.ShowBitmap();
				score_star_2.ShowBitmap();
				score_star_3.ShowBitmap();
				point[i].ShowBitmap();
				if (i >= place[0] + 3) {
					score_star.SetFrameIndexOfBitmap(1);
				}

				if (i >= place[1] + 3) {
					score_star_2.SetFrameIndexOfBitmap(1);
				}

				if (i >= 99) {
					score_star_3.SetFrameIndexOfBitmap(1);
				}

			}

		}

		void start_ui_show() {
			start_loading.ShowBitmap();
		}
		void rankchoose_ui_show() {
			rank_choose_map.ShowBitmap();
			rank_down_button.ShowBitmap();
			for (int i = 0; i < 20; i++) {
				rank[i].ShowBitmap();
			}
		}
		void rankchoose_ui_unshow() {
			rank_choose_map.UnshowBitmap();
			rank_down_button.UnshowBitmap();
			for (int i = 0; i < 20; i++) {
				rank[i].UnshowBitmap();
			}
		}
		void rankchoose_ui_2_show() {
			rank_choose_map.ShowBitmap();
			rank_up_button.ShowBitmap();

			for (int i = 10; i < 30; i++) {
				rank[i].ShowBitmap();
			}
		}
		void Point() {
			for (int i = 0; i < 100; i++) {
				point[i].LoadBitmapByString({ "resources/score/blue-1.bmp" });
			}
			point[0].SetTopLeft(228, 20);
			for (int i = 1; i < 100; i++) {
				point[i].SetTopLeft(point[i - 1].GetLeft() + point[i - 1].GetWidth(), point[i - 1].GetTop());
			}
		}

		void Point_Show(int score) {

		}

		bool IS_PLAY_BUTTON(CPoint point) {
			return (600 > point.x && point.x > 150) && (800 > point.y && point.y > 640) && start_loading.GetFrameIndexOfBitmap() == 2;
		}
		bool IS_DOWN_BUTTON(CPoint point) {
			int x = rank_down_button.GetLeft();
			int width = rank_down_button.GetWidth();
			int y = rank_down_button.GetTop();
			int height = rank_down_button.GetHeight();
			return (x + width > point.x && point.x > x) && (y + height > point.y && point.y > y);
		}
		bool IS_UP_BUTTON(CPoint point) {
			int x = rank_up_button.GetLeft();
			int width = rank_up_button.GetWidth();
			int y = rank_up_button.GetTop();
			int height = rank_up_button.GetHeight();
			return (x + width > point.x && point.x > x) && (y + height > point.y && point.y > y);
		}


		void RUN2() {
			board.LoadBitmapByString({ "resources/score/board.bmp" }, RGB(255, 255, 255));
			board.SetTopLeft(125, 150);
			Retry.LoadBitmapByString({ "resources/score/Retry.bmp" }, RGB(255, 255, 255));
			Retry.SetTopLeft(board.GetLeft() + 50, board.GetTop() + board.GetHeight() - 200);
			Home.LoadBitmapByString({ "resources/score/home.bmp" }, RGB(255, 255, 255));
			Home.SetTopLeft(Retry.GetLeft() + Retry.GetWidth(), Retry.GetTop());

		}
		void Win() {
			Win_background.LoadBitmapByString({ "resources/score/win_background.bmp" });
			Win_background.SetTopLeft(0, -30);
			Win_Bird.LoadBitmapByString({ "resources/score/win_bird.bmp" }, RGB(255, 255, 255));
			Win_Bird.SetTopLeft(0, 700);
			Next.LoadBitmapByString({ "resources/score/next.bmp" }, RGB(255, 255, 255));
			Next.SetTopLeft(Home.GetLeft() + Home.GetWidth(), Home.GetTop());
			Board_set();
		}

		void Fail() {
			Fail_background.LoadBitmapByString({ "resources/score/lose_background.bmp" });
			Fail_background.SetTopLeft(0, -100);
			Fail_Character.LoadBitmapByString({ "resources/score/lose_Character.bmp" }, RGB(255, 255, 255));
			Fail_Character.SetTopLeft(0, 700);
			Board_set();
		}
		bool IS_NEXT(CPoint point) {
			return Next.isClick_CMovingBitmap(Next, point);
		}

		bool IS_RETRY(CPoint point) {
			return Retry.isClick_CMovingBitmap(Retry, point);
		}

		bool IS_HOME(CPoint point) {
			return Home.isClick_CMovingBitmap(Home, point);
		}
		void Board_set() {
			board.LoadBitmapByString({ "resources/score/board.bmp" }, RGB(255, 255, 255));
			board.SetTopLeft(125, 150);
			Close.LoadBitmapByString({ "resources/score/close.bmp" }, RGB(255, 255, 255));
			Close.SetTopLeft(board.GetLeft() + board.GetWidth() - 110, board.GetTop() + 80);
			star.LoadBitmapByString({ "resources/score/0star.bmp","resources/score/1star.bmp","resources/score/2stars.bmp","resources/score/3stars.bmp" }, RGB(255, 255, 255));
			star.SetTopLeft(board.GetLeft(), board.GetTop() + 200);
			star.SetAnimation(1000, true);
			Retry.LoadBitmapByString({ "resources/score/Retry.bmp" }, RGB(255, 255, 255));
			Retry.SetTopLeft(board.GetLeft() + 40, board.GetTop() + board.GetHeight() - 200);
			Home.LoadBitmapByString({ "resources/score/home.bmp" }, RGB(255, 255, 255));
			Home.SetTopLeft(Retry.GetLeft() + Retry.GetWidth(), Retry.GetTop());
		}

		void win_ui_show(int x = 0) {
			Win_background.ShowBitmap();
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
			Next.ShowBitmap();
			Win_Bird.ShowBitmap();
			Retry.ShowBitmap();
			Home.ShowBitmap();
		}

		void Setting_Show() {
			Setting.ShowBitmap();
		}
		void Setting_UnShow() {
			Setting.UnshowBitmap();
		}
		void Setting_RUN_show() {
			board.ShowBitmap();
			Close.ShowBitmap();
			Retry.ShowBitmap();
			Home.ShowBitmap();
		}
		void Setting_RUN_Unshow() {
			board.UnshowBitmap();
			Close.UnshowBitmap();
			Retry.UnshowBitmap();
			Home.UnshowBitmap();
		}

		void Fail_ui_show() {
			Fail_background.ShowBitmap();
			board.ShowBitmap();
			star.SetFrameIndexOfBitmap(0);
			star.ShowBitmap();
			Fail_Character.ShowBitmap();
			Retry.ShowBitmap();
			Home.ShowBitmap();
		}

		int IS_RANK_BUTTON_1(CPoint point) {
			for (int i = 0; i < 20; i++) {
				if (rank[i].isClick_CMovingBitmap(rank[i], point)) {
					return i;
				}
				/*
				int x = rank[i].GetLeft();
				int width = rank[i].GetWidth();
				int y = rank[i].GetTop();
				int height = rank[i].GetHeight();
				if ((x + width > point.x && point.x > x) && (y + height > point.y && point.y > y)) {
					return i;
				}
				else {
					continue;
				}
				*/
			}
			return -1;
		}
		int IS_RANK_BUTTON_2(CPoint point) {
			for (int i = 10; i < 30; i++) {
				if (rank[i].isClick_CMovingBitmap(rank[i], point)) {
					return i;
				}
				/*
				int x = rank[i].GetLeft();
				int width = rank[i].GetWidth();
				int y = rank[i].GetTop();
				int height = rank[i].GetHeight();
				if ((x + width > point.x && point.x > x) && (y + height > point.y && point.y > y)) {
					return i;
				}
				else {
					continue;
				}*/
			}
			return -1;
		}
		bool IS_SETTING(CPoint point) {
			return Setting.isClick_CMovingBitmap(Setting, point);
		}

		bool IS_CLOSE(CPoint point) {
			return Close.isClick_CMovingBitmap(Close, point);
		}

	private:
		CMovingBitmap start_loading;
		CMovingBitmap start_ui;
		CMovingBitmap rank_choose_map;
		CMovingBitmap rank_down_button;
		CMovingBitmap rank_up_button;
		CMovingBitmap rank[30];
		CMovingBitmap point[100];
		CMovingBitmap Win_Bird;
		CMovingBitmap Game_background;
		CMovingBitmap score_board;
		CMovingBitmap score_star;
		CMovingBitmap score_star_2;
		CMovingBitmap score_star_3;
		CMovingBitmap Win_background;
		CMovingBitmap Fail_background;
		CMovingBitmap Fail_Character;
		CMovingBitmap board;
		CMovingBitmap star;
		CMovingBitmap Retry;
		CMovingBitmap Next;
		CMovingBitmap Home;
		CMovingBitmap Setting;
		CMovingBitmap Close;
	};
}
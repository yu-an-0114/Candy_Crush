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
	class Score {
	public:
		static int score;
		void score_strip() {
			for (int i = 0; i < 100; i++) {
				score_point[i].LoadBitmapByString({ "resources/score/blue-1.bmp" });
			}
			score_point[0].SetTopLeft(228, 20);
			for (int i = 1; i < 100; i++) {
				score_point[i].SetTopLeft(score_point[i - 1].GetLeft() + score_point[i - 1].GetWidth(), score_point[i - 1].GetTop());
			}
		}
		int score_board_show(int score, int *place, int goal = 10000) {
			score_board.ShowBitmap();
			int index = 0;
			//goal = 10000;
			int percentage = (score * 100 / goal);
			score_star.ShowBitmap();
			score_star_2.ShowBitmap();
			score_star_3.ShowBitmap();
			score_star.SetFrameIndexOfBitmap(0);
			score_star_2.SetFrameIndexOfBitmap(0);
			score_star_3.SetFrameIndexOfBitmap(0);
			for (int i = 1; i < percentage; i++) {

				if (i == 100) {
					break;
				}
				score_star.ShowBitmap();
				score_star_2.ShowBitmap();
				score_star_3.ShowBitmap();
				score_point[i].ShowBitmap();
				if (i >= place[0] + 3) {
					score_star.SetFrameIndexOfBitmap(1);
					index = 1;
				}

				if (i >= place[1] + 3) {
					score_star_2.SetFrameIndexOfBitmap(1);
					index = 2;
				}

				if (i >= 98) {
					score_star_3.SetFrameIndexOfBitmap(1);
					index = 3;
				}
			}
			return index;
		}
		
		void score_background_init(int *place) {

			score_board.LoadBitmapByString({ "resources/score/score_board2.bmp" }, RGB(255, 255, 255));
			score_board.SetTopLeft(-20, 0);
			score_strip();
			score_star.LoadBitmapByString({ "resources/score/unlight_star.bmp","resources/score/light_star.bmp" }, RGB(255, 255, 255));
			score_star.SetTopLeft(score_point[place[0]].GetLeft(), score_point[28].GetTop() - 5);
			score_star.SetFrameIndexOfBitmap(0);
			score_star_2.LoadBitmapByString({ "resources/score/unlight_star.bmp","resources/score/light_star.bmp" }, RGB(255, 255, 255));
			score_star_2.SetTopLeft(score_point[place[1]].GetLeft(), score_point[61].GetTop() - 5);
			score_star_2.SetFrameIndexOfBitmap(0);
			score_star_3.LoadBitmapByString({ "resources/score/unlight_star.bmp","resources/score/light_star.bmp" }, RGB(255, 255, 255));
			score_star_3.SetTopLeft(score_point[95].GetLeft(), score_point[95].GetTop() - 5);
			score_star_3.SetFrameIndexOfBitmap(0);
		}
		void scoreShow() {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "Futura", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 20, 60, "Score:" + to_string(score));
			CDDraw::ReleaseBackCDC();
		}
	private:
		CMovingBitmap score_board;
		CMovingBitmap score_star;
		CMovingBitmap score_star_2;
		CMovingBitmap score_star_3;
		CMovingBitmap score_point[100];
		//CTextDraw score_text;
	};
}

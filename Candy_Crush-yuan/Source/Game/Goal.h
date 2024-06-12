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
	class Goal {
	public:
		Goal()
		{

		}
		~Goal()
		{

		}
		int goal[3] = { 0,0,0 };
		CMovingBitmap goalicon[3];
		CMovingBitmap check[3];
		int rankgoal[30][3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
								{6,7,8}, {7,8,9}, {8,9,10}, {6,7,8}, {10,10,10},
								{11,12,13}, {14,15,16}, {17,10,9}, {8,9,10}, {15,16,17},
								{16,17,18}, {17,18,19}, {10,20,21}, {22,23,24}, {23,24,25},
								{16,17,18}, {17,18,19}, {10,20,21}, {22,23,24}, {23,24,25},
								{16,17,18}, {17,18,19}, {10,20,21}, {22,23,24}, {23,24,25} };

		int goalnumber[30][3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
								 {6,6,6}, {7,7,7}, {8,8,8}, {9,9,9}, {9,9,9},
								 {10,10,10}, {11,11,11}, {12,12,12}, {13,13,13}, {14,14,14},
								 {15,15,15}, {16,16,16}, {17,17,17}, {18,18,18}, {19,19,19},
								 {20,20,20}, {21,21,21}, {22,22,22}, {23,23,23}, {24,24,24},
								 {25,25,25}, {26,26,26}, {27,27,27}, {28,28,28}, {29,29,29} };
		void GoalSetting(int level) {
			for (int i = 0; i < 3; i++) {
				goalicon[i].LoadBitmapByString({ "resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp",
					"resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,
					"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,
					"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,
					"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,
					"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,
					"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,
					"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,
					"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp",
					"resources/cherry.bmp","resources/block/chocolate.bmp","resources/block/glass.bmp","resources/block/sugar.bmp","resources/block/X_block.bmp" }, RGB(255, 255, 255));
				check[i].LoadBitmapByString({ "resources/check.bmp" }, RGB(255, 255, 255));
				goalicon[i].SetTopLeft(225 + goalicon[i].GetWidth()*i + i * 40, 75);

				check[i].SetTopLeft(goalicon[i].GetLeft() + goalicon[i].GetWidth() + 5, 75 + 15);
			}
			goalInit(level);

		}



		int GetGoalIndex(int rank, int place) {
			return rankgoal[rank][place];
		}

		void SetGoal(int index, int value) {
			goal[index] -= value;
		}

		void goalInit(int rank) {
			for (int i = 0; i < 3; i++) {
				goal[i] = goalnumber[rank][i];
			}
		}

		void goalShow(int level) {
			if (goal[0] == -1) {
				return;
			}
			for (int i = 0; i < 3; i++) {
				goalicon[i].SetFrameIndexOfBitmap(rankgoal[level][i]);
				goalicon[i].ShowBitmap();
				if (goal[i] == 0) {
					check[i].ShowBitmap(0.8);
				}
				else {
					CDC *pDC = CDDraw::GetBackCDC();
					CTextDraw::ChangeFontLog(pDC, 20, "¡PL?n??????", RGB(255, 255, 255));
					CTextDraw::Print(pDC, check[i].GetLeft() + 7, check[i].GetTop(), to_string(goal[i]));
					//CTextDraw::Print(pDC, X + 5, Y + 40, to_string(20));
					CDDraw::ReleaseBackCDC();
				}

			}
		}

		void RANK(int A) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "¡PL?n??????", RGB(255, 255, 255));
			//CTextDraw::Print(pDC, 500, 900, "Rank:" + to_string(rank));
			CTextDraw::Print(pDC, 400, 900, "Rank:" + to_string(A));
			CDDraw::ReleaseBackCDC();
		}
		void TEST(int A) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "¡PL?n??????", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 100, 900, "Test:" + to_string(A));
			CDDraw::ReleaseBackCDC();
		}


		CMovingBitmap goal1;
		CMovingBitmap goal2;
		CMovingBitmap goal3;
		CMovingBitmap check1;
		CMovingBitmap check2;
		CMovingBitmap check3;
	};
}
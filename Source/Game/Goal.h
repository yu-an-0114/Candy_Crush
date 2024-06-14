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
								{6,7,17}, {7,11,13}, {8,12,16}, {6,7,18}, {3,4,5},
								{11,12,21}, {11,14,16}, {9,10,17}, {8,9,10}, {15,16,20},
								{10,11,26}, {14,18,26}, {10,20,21}, {22,25,26}, {23,25,26},
								{16,17,26}, {17,18,26}, {10,20,27}, {22,27,29}, {23,24,27},
								{16,17,30}, {26,27,29}, {26,29,30}, {2,3,28}, {26,27,28} };

		int goalnumber[30][3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
								 {6,1,1}, {1,2,2}, {2,2,2}, {15,2,2}, {20,20,20},
								 {2,2,2}, {2,2,2}, {2,2,2}, {2,2,2}, {2,2,2},
								 {1, 2 ,1}, {2,2,3}, {2,2,2}, {3,3,2}, {2,2,19},
								 {2,2,4}, {2,2,2}, {2,2,64}, {2,16,8}, {2,2,8},
								 {2,2,20}, {1,22,8}, {3,3,3}, {10,10,30}, {2,40,20} };
		void GoalSetting(int level) {
			for (int i = 0; i < 3; i++) {
				if (rankgoal[level][i] == 0) {
					continue;
				}
				goalicon[i].LoadBitmapByString({ "resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp",
					"resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,
					"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,
					"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,
					"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,
					"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,
					"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,
					"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,
					"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp",
					"resources/cherry.bmp","resources/block/glass.bmp","resources/block/sugar.bmp","resources/block/X_block.bmp","resources/bomb/bomb.bmp" }, RGB(255, 255, 255));//30炸彈    31巧克力
				check[i].LoadBitmapByString({"resources/check.bmp" }, RGB(255, 255, 255));
				goalicon[i].SetTopLeft(225 + 105*i , 75);

				check[i].SetTopLeft(280 + i*105 , 75 + 10);
			}
			goalInit(level);

		}
		bool Pass(int goalCheck=3){
			int check = 0;
			for (int i = 0; i < 3; i++) {
				if (goal[i] <= 0) {
					check += 1;
					continue;
				}
			}
			if (check == goalCheck) {
				return true;
			}
			return false;
		}


		int GetGoalIndex(int level, int place) {
			return rankgoal[level][place];
		}

		void SetGoal(int index) {
			for (int i = 0; i < 3; i++) {
				if (goalicon[i].GetFrameIndexOfBitmap() == index) {
					goal[i] -= 1;
				}
			}
		}

		void goalInit(int level) {
			for (int i = 0; i < 3; i++) {
				goal[i] = goalnumber[level][i];
			}
		}

		void goalShow(int level) {
			//if (goal[0] == -1) {
			//	return;
			//}
			for (int i = 0; i < 3; i++) {
				if (rankgoal[level][i] == 0) {
					continue;
				}
				goalicon[i].SetFrameIndexOfBitmap(rankgoal[level][i]);
				goalicon[i].ShowBitmap();
				if (goal[i] <= 0) {
					check[i].ShowBitmap();
				}
				else {
					CDC *pDC = CDDraw::GetBackCDC();
					CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
					CTextDraw::Print(pDC, 295 + i * 108, 90, to_string(goal[i]));
					//CTextDraw::Print(pDC, X + 5, Y + 40, to_string(20));
					CDDraw::ReleaseBackCDC();
				}

			}
		}

		void RANK(int A) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			//CTextDraw::Print(pDC, 500, 900, "Rank:" + to_string(rank));
			CTextDraw::Print(pDC, 400, 900, "Rank:" + to_string(A));
			CDDraw::ReleaseBackCDC();
		}
		void TEST(int A) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 100, 900, "Test:" + to_string(A));
			CDDraw::ReleaseBackCDC();
		}


	};
}
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
	class Goal : public CMovingBitmap {
	public:
		Goal() {

		}
		int goal[3] = { 0,0,0 };


		int rankgoal[20][3] = { {1,2,3}, {2,3,4}, {3,4,5}, {4,5,6}, {5,6,7},
								{6,7,8}, {7,8,9}, {8,9,10}, {6,7,8}, {10,10,10},
								{11,12,13}, {14,15,16}, {17,10,9}, {8,9,10}, {15,16,17},
								{16,17,18}, {17,18,19}, {10,20,21}, {22,23,24}, {23,24,25} };

		int goalnumber[20][3] = { {10,10,10}, {10,10,10}, {5,5,5}, {4,4,4}, {5,5,5},
								 {6,6,6}, {7,7,7}, {8,8,8}, {9,9,9}, {9,9,9},
								 {10,10,10}, {11,11,11}, {12,12,12}, {13,13,13}, {14,14,14},
								 {15,15,15}, {16,16,16}, {17,17,17}, {18,18,18}, {19,19,19} };
		void GoalSetting(int level) {
			goal1.LoadBitmapByString({ "resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp",
				"resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,
				"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,
				"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,
				"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,
				"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,
				"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,
				"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,
				"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp" }, RGB(255, 255, 255));
			goal1.SetTopLeft(245, 75);

			goal2.LoadBitmapByString({ "resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp",
				"resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,
				"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,
				"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,
				"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,
				"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,
				"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,
				"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,
				"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp" }, RGB(255, 255, 255));
			goal2.SetTopLeft(goal1.GetLeft() + goal1.GetWidth() + 35, goal1.GetTop());

			goal3.LoadBitmapByString({ "resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp",
				"resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,
				"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,
				"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,
				"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,
				"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,
				"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,
				"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,
				"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp" }, RGB(255, 255, 255));
			goal3.SetTopLeft(goal2.GetLeft() + goal2.GetWidth() + 35, goal1.GetTop());

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
			goal1.SetFrameIndexOfBitmap(rankgoal[level][0]);
			goal1.ShowBitmap();
			goal2.SetFrameIndexOfBitmap(rankgoal[level][1]);
			goal2.ShowBitmap();
			goal3.SetFrameIndexOfBitmap(rankgoal[level][2]);
			goal3.ShowBitmap();

		}
		void goalShow(int index, int X, int Y) {

			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, X + 7, Y + 30, to_string(goal[index]));
			//CTextDraw::Print(pDC, X + 5, Y + 40, to_string(20));
			CDDraw::ReleaseBackCDC();
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
		CMovingBitmap goal1;
		CMovingBitmap goal2;
		CMovingBitmap goal3;
	};
}

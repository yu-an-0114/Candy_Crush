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
	class LevelCheck {
	public:
		static int step;
		static int rank;
		static int score;

		int goal[3] = {0,0,0};

		int rankstep[20] = { 20, 20, 20, 20, 10,
							 10, 10, 10, 10, 10,
							 10, 10, 10, 10, 10,
							 10, 10, 10, 10, 10, };
		int rankgoal[20][3] = { {1,2,3}, {2,3,4}, {3,4,5}, {4,5,6}, {5,6,7},
								{6,7,8}, {7,8,9}, {8,9,10}, {6,7,8}, {10,10,10},
								{11,12,13}, {14,15,16}, {17,10,9}, {8,9,10}, {15,16,17},
								{16,17,18}, {17,18,19}, {10,20,21}, {22,23,24}, {23,24,25}, };
		int goalnumber[20][3] = {{10,10,10}, {10,10,10}, {5,5,5}, {4,4,4}, {5,5,5},
								 {6,6,6}, {7,7,7}, {8,8,8}, {9,9,9}, {9,9,9},
								 {10,10,10}, {11,11,11}, {12,12,12}, {13,13,13}, {14,14,14},
								 {15,15,15}, {16,16,16}, {17,17,17}, {18,18,18}, {19,19,19} };
		LevelCheck() {

		}
		
		int stepInit(int level) {
			return rankstep[level];
		}

		int stepMove(int step) {
			return step - 1;
		}

		int GetGoalIndex(int place) {
			return rankgoal[rank][place];
		}

		void SetGoal(int index,int value) {
			goal[index] -= value;
		}

		void SetGoal() {
			for (int i = 0; i < 3; i++) {
				goal[i] = goalnumber[rank][i];
			}
		}
		
		int SetGoal(int index) {
			return goalnumber[rank][index];
		}


		bool IsnewGame(int level, int step) {
			return step == rankstep[level];
		}

		void SCORE() {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 20, 60, "Score:" + to_string(score));
			CDDraw::ReleaseBackCDC();
		}

		void STEP() {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 20, 90, "Step:" + to_string(step));
			CDDraw::ReleaseBackCDC();
		}
		void GOAL(int index,int X,int Y) {

			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, X + 7, Y + 30, to_string(goal[index]));
			//CTextDraw::Print(pDC, X + 5, Y + 40, to_string(20));
			CDDraw::ReleaseBackCDC();
		}

		void RANK(int A) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 500, 900, "Rank:" + to_string(rank));
			CTextDraw::Print(pDC, 400, 900, "Rank:" + to_string(A));
			CDDraw::ReleaseBackCDC();
		}

		void TEST(int A, int B, int C) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 100, 900, "Test:" + to_string(A) + to_string(B) + to_string(C));
			CDDraw::ReleaseBackCDC();
		}
	};
}

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
		int rankgoal[20][3] = { {1,2,3}, {2,3,4}, {3,4,5}, {0,0,0}, {0,0,0},
								{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
								{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
								{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, };
		int goalnumber[20][3] = {{10,10,10}, {10,10,10}, {5,5,5}, {4,4,4}, {5,0,0},
								 {6,0,0}, {7,0,0}, {8,0,0}, {9,9,0}, {9,9,9},
								 {10,10,10}, {11,11,11}, {12,12,12}, {13,13,13}, {14,14,14},
								 {15,15,15}, {16,16,16}, {17,17,17}, {18,18,18}, {19,19,19} };
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
			goal[index] = value;
		}

		void SetGoal() {
			for (int i = 0; i < 3; i++) {
				goal[i] = goalnumber[rank][0];
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
			CTextDraw::Print(pDC, 20, 20, "Score:" + to_string(score));
			CDDraw::ReleaseBackCDC();
		}

		void STEP() {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 200, 20, "Step:" + to_string(step));
			CDDraw::ReleaseBackCDC();
		}
		void GOAL(int index,int X,int Y) {

			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, X + 5, Y + 20, to_string(goal[0]));
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

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

	class Effect {

	public:
		Effect() : effect(10, vector<int>(10, 0)), effectlevel(10, vector<CMovingBitmap>(10)) {
		}

		~Effect() {

		}

		void effectLoad() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					effectlevel[i][j].LoadBitmapByString({
						"resources/special_effect/effect1.bmp",
						"resources/special_effect/effect2.bmp",
						"resources/special_effect/effect3.bmp",
						"resources/special_effect/effect4.bmp",
						"resources/special_effect/effect5.bmp",
						"resources/special_effect/effect_base.bmp"
						}, RGB(255, 255, 255));
					effectlevel[i][j].SetTopLeft(10 + 76 * j, 150 + 76 * i);
					effectlevel[i][j].SetAnimation(1000, true);
				}
			}
		}

		void shine(int X, int Y, int i = 1) {
			if (X < 10 && Y < 10) {
				effect[X][Y] = i; // 
			}
		}

		void Unshine(int X, int Y) {
			if (X < 10 && Y < 10) {
				effect[X][Y] = 0; // 
			}
		}

		void TEST3(int A) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 150, 900 + 10, "TEST3:" + to_string(A));
			CDDraw::ReleaseBackCDC();
		}

		void TEST2(int A, int B, int C) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 100 + int(A) * 5, 1000 + 10 * int(B), "TEST2:");
			CDDraw::ReleaseBackCDC();
		}

		void Show_effect() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (effect[i][j] == 1) {
						effectlevel[i][j].ShowBitmap();
					}
					else if (effect[i][j] == 2) {
						effectlevel[i][j].SetFrameIndexOfBitmap(5);
						effectlevel[i][j].ShowBitmap();
						effectlevel[i][j].ToggleAnimation();
					}
					Unshine(i, j);
				}
			}
		}

	private:
		vector<vector<CMovingBitmap>> effectlevel;
		vector<vector<int>> effect;
	};

}

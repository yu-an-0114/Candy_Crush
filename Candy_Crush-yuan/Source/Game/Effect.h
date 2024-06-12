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


		void effectLoad() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					effectlevel[i][j].LoadBitmapByString({ "resources/special_effect/effect1.bmp" ,"resources/special_effect/effect2.bmp" ,"resources/special_effect/effect3.bmp" ,"resources/special_effect/effect4.bmp" ,"resources/special_effect/effect5.bmp","resources/special_effect/effect_base.bmp" }, RGB(255, 255, 255));
					effectlevel[i][j].SetTopLeft(10 + 76 * j, 150 + 76 * i);
					effectlevel[i][j].SetAnimation(1000, true);
				}
			}
		}

		void shine(int X, int Y, int i = 1) {
			effect[X][Y] = i;
		}

		void Unshine(int X, int Y) {
			effect[X][Y] = 0;
		}
		void TEST3(int A) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "¡PL?n??????", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 150, 900 + 10, "TEST3:" + to_string(A));
			CDDraw::ReleaseBackCDC();
		}
		void TEST2(int A, int B, int C) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "¡PL?n??????", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 100 + int(A) * 5, 1000 + 10 * int(B), "TEST2:");
			CDDraw::ReleaseBackCDC();
		}
		void Show_effect() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					TEST2(i, j, effect[i][j]);
					TEST3(effect[i][j]);
					if (effect[i][j] == 1) {
						TEST2(i, j, effect[i][j]);
						effectlevel[i][j].ShowBitmap();
						//effect[i][j].ToggleAnimation();
						//time.Delay(5);

					}
					else if (effect[i][j] == 2) {
						effectlevel[i][j].SetFrameIndexOfBitmap(5);
						//effect[i][j].SetFrameIndexOfBitmap(3);
						effectlevel[i][j].ShowBitmap();
						effectlevel[i][j].ToggleAnimation();
						//time.Delay(5);

					}
					Unshine(i, j);
				}


			}
		}
		CMovingBitmap effectlevel[10][10];
		int effect[10][10] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		};
	};

}
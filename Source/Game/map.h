
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
#include <typeinfo>

#include "MapLevel.h"
#include "Cherry.h"
#include "Candy.h"
#include "CandyLattice.h"
using namespace game_framework;

namespace game_framework {
	class Map {
	public:
		void build_map(int level) {
			unit_candy_lattice.LoadBitmapByString({ "resources/CandyLattice.bmp" });
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 0) {
						continue;
					}
					else {
						candy_lattice[i][j].LoadBitmapByString({ "resources/CandyLattice.bmp" },RGB(255,255,255));
						Sleep(1);
						candy_lattice[i][j].SetTopLeft(10 + unit_candy_lattice.GetWidth()*j, 150 + unit_candy_lattice.GetHeight()*i);
						candy[i][j].LoadBitmapByString({ "resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp","resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp" }, RGB(255, 255, 255));
						Sleep(1);
						set_candy_lattice_center(i, j, candy);
						candy[i][j].SetFrameIndexOfBitmap(0);
						if (map_level[level][i][j] == 1) {
							int RandNum = rand() % 6 + 1;
							candy[i][j].SetFrameIndexOfBitmap(RandNum);
						}
					}
				}
			}	
		}
		void show_map(int level) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (candy_lattice[i][j].IsBitmapLoaded()) {
						candy_lattice[i][j].ShowBitmap();
					}
					if (map_level[level][i][j] == 0) {

						continue;
					}
					//candy_lattice[i][j].ShowBitmap();
				}
			}
			
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (candy[i][j].IsBitmapLoaded()) {
						candy[i][j].ShowBitmap();
					}
					if (map_level[level][i][j] == 0) {
						continue;
					}
					else {
						
						if (map_level[level][i][j] == 1) {
							
						}
						else {
							//candy[i][j].UnshowBitmap();
						}
					}
				}
			}
		}
		template <typename T>
		void set_candy_lattice_center(int x, int y, T& object) {
			object[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - object[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - object[x][y].GetHeight()) / 2);
		}

		void map_level_text(int level) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 10, "·L³n¥¿¶ÂÅé", RGB(255, 255, 255));
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					CTextDraw::Print(pDC,100+ 15*j, 15*i, to_string(map_level[level][i][j]));
				}
			}
			CTextDraw::Print(pDC, 300 , 15 , to_string(level));
			CDDraw::ReleaseBackCDC();
		}
		CandyLattice unit_candy_lattice;
		CandyLattice candy_lattice[10][10];
		Candy candy[10][10];
		Cherry cherry[10][10];
		CSpecialEffect time;
	};
}


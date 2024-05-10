
//#ifdef MAP_H
//#define MAP_H
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
#include "MapLevel.h"

using namespace std;

namespace game_framework {
	class Map {
	public:
	
		
		void Build_map(int level) {
			unitMap.LoadBitmapByString({ "resources/CandyLattice.bmp" });
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (maplevel.mapLevel[level][i][j] == 0) {
						continue;
					}
					map[i][j].LoadBitmapByString({ "resources/CandyLattice.bmp" });
					map[i][j].SetTopLeft(10 + unitMap.GetWidth()*j, 150 + unitMap.GetHeight()*i);
					candy[i][j].LoadBitmapByString({"resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp","resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp" }, RGB(255, 255, 255));
					int RandNum = rand() % 6 + 1;		
					
					candy[i][j].SetFrameIndexOfBitmap(RandNum);
					candy[i][j].SetTopLeft(map[i][j].GetLeft() + (unitMap.GetWidth() - candy[i][j].GetWidth()) / 2, map[i][j].GetTop() + (unitMap.GetHeight() - candy[i][j].GetHeight()) / 2);
				}
			}
		}

		void Show_map(int level) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (maplevel.mapLevel[level][i][j] == 0) {
						continue;
					}
					map[i][j].ShowBitmap();
				}
			}
			
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (maplevel.mapLevel[level][i][j] == 0) {
						continue;
					}
					candy[i][j].ShowBitmap();
				}
			}
		}

		void candy_down(int level) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					int candyLatticeEmpty = 0;
					if (maplevel.mapLevel[level][i][j] == 0) {
						continue;
					}
					int k = i;
					if (candy[i][j].GetFrameIndexOfBitmap() == 0) {
						score = score + 10;
						k = i;	
						while (1) {
							if (k < Map_level_lattice_top_not_empty_num(j,level)) {
								break;
							}
							if (maplevel.mapLevel[level][k][j] == 0) {
								k--;
								candyLatticeEmpty++;
								continue;
							}
							if (k == Map_level_lattice_top_not_empty_num(j,level)) {
								
								int RandNum = rand() % 6 + 1;
								candy[k][j].SetFrameIndexOfBitmap(RandNum);
							}
							else {
								candy[k][j].SetFrameIndexOfBitmap(candy[k - candyLatticeEmpty - 1][j].GetFrameIndexOfBitmap());
							}
							candy[k][j].SetTopLeft(map[k][j].GetLeft() + (unitMap.GetWidth() - candy[k][j].GetWidth()) / 2, map[k][j].GetTop() + (unitMap.GetHeight() - candy[k][j].GetHeight()) / 2);
							k--;
						}
					}
				}
			}
		}

		int Map_level_lattice_top_not_empty_num(int col,int level) {
			for (int i = 0; i < 10; i++) {
				if (maplevel.mapLevel[level][i][col] != 0) {
					return i;
				}
			}
			return 0;
		}

		int Candy_Connet(int x, int y, bool checkRow) {
			int x1 = x;
			int y1 = y;
			if (checkRow) {
				while (isCandySameColor(x,y,x1,y1)) {
					y1++;
				}
				return y1 - y + 1;
			}
			else {
				while (isCandySameColor(x, y, x1, y1)) {
					x1++;
				}
				return x1 - x + 1;	
			}
		}

		void Candy_Element(int clickX, int clickY, int changeX, int changeY, int level) {
			int i = 0;
			while (1) {
				int j = 0;
				while (1) {
					if (maplevel.mapLevel[level][i][j] == 0) {
						j++;
						continue;
					}
					if (candy[i][j].GetFrameIndexOfBitmap() == 0 ) {
						j++;
						continue;
					}
					int k_row = j;
					int sum_row = 0;
					while (1) {
						if (maplevel.mapLevel[level][i][k_row] == 0) {
							sum_row = 0;
							break;
						}
						if (isCandySameColor(i, j, i, k_row)) {
							sum_row++;
						}
						else {
							candy_upgrade(clickX, clickY, changeX, changeY, i, j, sum_row, true, level);
							sum_row = 0;
							break;
						}

						k_row++;
						if (k_row >= 10) {
							candy_upgrade(clickX, clickY, changeX, changeY, i, j, sum_row, true, level);
							sum_row = 0;
							break;
						}
					}
					int k_col = i;
					int sum_col = 0;
					while (1) {
						if (maplevel.mapLevel[level][i][k_col] == 0) {
							sum_col = 0;
							break;
						}
						if (isCandySameColor(i, j, k_col, j)) {
							sum_col++;
						}
						else {
							candy_upgrade(clickX, clickY, changeX, changeY, i, j, sum_col, false, level);
							sum_col = 0;
							break;
						}
						k_col++;
						if (k_col >= 10) {
							candy_upgrade(clickX, clickY, changeX, changeY, i, j, sum_col, false, level);
							sum_col = 0;
							break;
						}
					}
					j++;
					if (j >= 10) {
						break;
					}
				}
				i++;
				if (i >= 10) {
					break;
				}
			}
		}
		bool isCandySameColor(int i, int j, int x, int y) {
			int color_num = 0;
			int color_num2 = 0;
			if (candy[i][j].GetFrameIndexOfBitmap() == 25 || candy[x][y].GetFrameIndexOfBitmap() == 25) {
				return false;
			}
			if (candy[i][j].GetFrameIndexOfBitmap() > 6) {
				if (candy[i][j].GetFrameIndexOfBitmap() % 3 == 0) {
					color_num = (int)ceil((candy[i][j].GetFrameIndexOfBitmap() - 6) / 3);
				}
				else {
					color_num = (int)ceil((candy[i][j].GetFrameIndexOfBitmap() - 6) / 3) + 1;
				}
			}
			else {
				color_num = candy[i][j].GetFrameIndexOfBitmap();
			}
			if (candy[x][y].GetFrameIndexOfBitmap() > 6) {
				if (candy[x][y].GetFrameIndexOfBitmap()% 3 == 0){
					color_num2 = (int)ceil((candy[x][y].GetFrameIndexOfBitmap() - 6) / 3);
				}
				else {
					color_num2 = (int)ceil((candy[x][y].GetFrameIndexOfBitmap() - 6) / 3)+1;
				}
			}
			else {
				color_num2 = candy[x][y].GetFrameIndexOfBitmap();
			}
			return color_num == color_num2;
		}
		void candy_change(int i, int j, int x, int y,int level) {
			int num = candy[i][j].GetFrameIndexOfBitmap();
			candy[i][j].SetFrameIndexOfBitmap(candy[x][y].GetFrameIndexOfBitmap());
			candy[x][y].SetFrameIndexOfBitmap(num);
			candy[x][y].SetTopLeft(map[x][y].GetLeft() + (map[x][y].GetWidth() - candy[x][y].GetWidth()) / 2, map[x][y].GetTop() + (map[x][y].GetHeight() - candy[x][y].GetHeight()) / 2);
			candy[i][j].SetTopLeft(map[i][j].GetLeft() + (map[i][j].GetWidth() - candy[i][j].GetWidth()) / 2, map[i][j].GetTop() + (map[i][j].GetHeight() - candy[i][j].GetHeight()) / 2);
			if (candy[i][j].GetFrameIndexOfBitmap() == 25) {
				for (int k = 0; k < 10; k++) {
					for (int z = 0; z < 10; z++) {
						if (maplevel.mapLevel[level][k][z] == 0) {
							continue;
						}
						if (k == x && z == y) {
							continue;
						}
						if (candy[k][z].GetFrameIndexOfBitmap() == candy[x][y].GetFrameIndexOfBitmap()) {
							candy[k][z].SetFrameIndexOfBitmap(0);
						}
					}
				}
				candy[i][j].SetFrameIndexOfBitmap(0);
			}
			else if (candy[x][y].GetFrameIndexOfBitmap() == 25) {
				for (int k = 0; k < 10; k++) {
					for (int z = 0; z < 10; z++) {
						if (maplevel.mapLevel[level][k][z] == 0) {
							continue;
						}
						if (k == i && z == j) {
							continue;
						}
						if (candy[k][z].GetFrameIndexOfBitmap() == candy[i][j].GetFrameIndexOfBitmap()) {
							candy[k][z].SetFrameIndexOfBitmap(0);
						}
					}
				}
				candy[x][y].SetFrameIndexOfBitmap(0);
			}
		}

		void candy_upgrade(int clickX, int clickY, int changeX, int changeY,int i,int j,int sum,bool isRow,int level) {
			/*if (candy[i][j].GetFrameIndexOfBitmap() != candy[clickX][clickY].GetFrameIndexOfBitmap()) {
				clickX = changeX;
				clickY = changeY;
			}*/
			
			if (isRow) {
				if (sum == 5) {
					for (int z = j; z < j + 5; z++) {
						if ((i == clickX && z == clickY ) || (z == j+2)) {
							if (Candy_Connet(i, z, false) >= 3) {
								for (int k = i; k < i + Candy_Connet(i, z, false); k++) {
									candy_skill(k, j + 2, level);
								}
							}
							candy[i][z].SetFrameIndexOfBitmap(25);
							continue;
						}
						candy_skill(i, z, level);
					}
				}
				else if (sum == 4) {
					for (int z = j; z < j + 4; z++) {
						if (z == clickY) {
							candy[i][z].SetFrameIndexOfBitmap(8 + (candy[i][z].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						candy[i][z].SetFrameIndexOfBitmap(0);
					}
				}
				
				else if (sum == 3) {	
					for (int k = i; k < i + 3; k++) {
						if (k >= 10) {
							break;
						}
						if (maplevel.mapLevel[level][k][j] == 0) {
							break;
						}
						if (!isCandySameColor(k, clickY, i, j)) {
							break;
						}
						if (k == i + 2) {
							candy[i][clickY].SetFrameIndexOfBitmap((9 + (candy[i][j].GetFrameIndexOfBitmap() - 1) * 3));
							for (int k1 = j; k1 < j + 3; k1++) {
								if (k1 == clickY) {
									continue;
								}
								candy_skill(i, k1,level);
								
							}
				
							for (int k1 = i; k1 < i + 3; k1++) {
								if (k1 == i) {
									continue;
								}
								candy_skill(k1, clickY, level);
							}
							return;
						}					
					}
			
					for (int z = j; z < j + 3; z++) {
						candy_skill(i, z, level);
					}
				}
			}
			else if(!isRow){
				if (sum == 5) {
					for (int k = j - 2; k < j; k++) {
						if (maplevel.mapLevel[level][i][k] == 0) {
							break;
						}
						if (k < 0 || i + 2 >= 10) {
							break;
						}
						if (!isCandySameColor(i+2, k, i, j)) {
							break;
						}
						if (k == j - 1) {
							for (int k1 = j - 2; k1 < j; k1++) {
								candy_skill(i+2, k1, level);
							
							}
						}
					}
					for (int z = i; z < i + 5; z++) {
						if ((z == clickX && j == clickY) || (z == changeX && j == changeY)) {
							candy[z][j].SetFrameIndexOfBitmap(25);
							continue;
						}
						candy_skill(z, j, level);

					}
				}
				else if (sum == 4) {
					for (int z = i; z < i + 4; z++) {
						if ((z == clickX && j == clickY) || (z == changeX && j == changeY)) {
							candy[z][j].SetFrameIndexOfBitmap(7 + (candy[z][j].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						candy_skill(z, j, level);
					}
				}
				else if (sum == 3) {
					for (int k = clickY; k > clickY - 3; k--) {
						if (k < 0 || i + 2 >= 10) {
							break;
						}
						if (!isCandySameColor(i + 2, k, i, j)) {
							break;
						}
						if (k == clickY - 2) {
							candy[clickX][clickY].SetFrameIndexOfBitmap((9 + (candy[i][j].GetFrameIndexOfBitmap() - 1) * 3));
							for (int k1 = j; k1 > j - 3; k1--) {
								if (k1 == clickY) {
									continue;
								}
								candy_skill(clickX, k1, level);
								//candy[clickX][k1].SetFrameIndexOfBitmap(0);
							}

							for (int k1 = i; k1 < i + 3; k1++) {
								if (k1 == clickX) {
									continue;
								}
								candy_skill(k1, j, level);
								//candy[k1][j].SetFrameIndexOfBitmap(0);
							}
							return;
						}
					}
					for (int k = clickY; k < clickY + 3; k++) {
						if (k >= 10 || i+2 >= 10) {
							break;
						}
						if (!isCandySameColor(i + 2, k, i, j)) {
							break;
						}
						if (k == clickY + 2) {
							candy[clickX][clickY].SetFrameIndexOfBitmap((9 + (candy[i][j].GetFrameIndexOfBitmap() - 1) * 3));
							for (int k1 = j; k1 < j + 3; k1++) {
								if (k1 == clickY) {
									continue;
								}
								candy_skill(clickX, k1, level);
							
							}

							for (int k1 = i; k1 < i + 3; k1++) {
								if (k1 == clickX) {
									continue;
								}
								candy_skill(k1, j, level);
								
							}
							return;
						}
					}
					for (int z = i; z < i + 3; z++) {
						candy_skill(z, j, level);
						
					}
				}
			}
		}
		
		void candy_skill(int x,int y,int level) {

			if (maplevel.mapLevel[level][x][y] == 0) {
				return;
			}
			
			if (candy[x][y].GetFrameIndexOfBitmap() < 7) {
				candy[x][y].SetFrameIndexOfBitmap(0);
			}
			else if (candy[x][y].GetFrameIndexOfBitmap() == 25) {
				return;
			}
			else if (candy[x][y].GetFrameIndexOfBitmap()%3 == 1 ) {
				for (int i = 0; i < 10; i++) {
					if (maplevel.mapLevel[level][x][i] == 0) {	
						continue;
					}
					candy[x][i].SetFrameIndexOfBitmap(0);
				}
			}
			else if (candy[x][y].GetFrameIndexOfBitmap() % 3 == 2) {
				for (int i = 0; i < 10; i++) {
					if (maplevel.mapLevel[level][i][y] == 0) {
						continue;
					}
					candy[i][y].SetFrameIndexOfBitmap(0);
				}
			}
			else {
				for (int i = 0; i < 2; i++) {
					if (x - 1 >= 0 && y - 1 >= 0) {
						if (maplevel.mapLevel[level][x-1][y-1] == 0) {
							
						}
						else {
							candy[x - 1][y - 1].SetFrameIndexOfBitmap(0);
						}
						
					}
					if (x - 1 >= 0) {
						if (maplevel.mapLevel[level][x - 1][y] == 0) {

						}
						else {
							candy[x - 1][y].SetFrameIndexOfBitmap(0);
						}
						
					}
					if (x - 1 >= 0 && y + 1 < 10) {
						if (maplevel.mapLevel[level][x - 1][y + 1] == 0) {

						}
						else {
							candy[x - 1][y + 1].SetFrameIndexOfBitmap(0);
						}
						
					}
					if (y - 1 >= 0) {
						if (maplevel.mapLevel[level][x][y - 1] == 0) {

						}
						else {
							candy[x][y - 1].SetFrameIndexOfBitmap(0);
						}
					}
					if (y + 1 < 10) {
						if (maplevel.mapLevel[level][x][y + 1] == 0) {

						}
						else {
							candy[x][y + 1].SetFrameIndexOfBitmap(0);
						}
						
					}
					if (x + 1 < 10 && y - 1 >= 0) {
						if (maplevel.mapLevel[level][x + 1][y - 1] == 0) {

						}
						else {
							candy[x + 1][y - 1].SetFrameIndexOfBitmap(0);
						}
					}
					if (x + 1 < 10) {
						if (maplevel.mapLevel[level][x + 1][y] == 0) {

						}
						else {
							candy[x + 1][y].SetFrameIndexOfBitmap(0);
						}
					}
					if (x + 1 < 10 && y + 1 < 10) {
						if (maplevel.mapLevel[level][x + 1][y + 1] == 0) {

						}
						else {
							candy[x + 1][y + 1].SetFrameIndexOfBitmap(0);
						}
					}
					candy_down(level);
					if (x < 9) {
						x = x + 1;
					}

				}
			
			candy[x][y].SetFrameIndexOfBitmap(0);
			}
		}
		

		void SCORE() {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "�L�n������", RGB(255, 255, 255));
			CTextDraw::Print(pDC,20, 20, "Score:"+ to_string(score));
			CDDraw::ReleaseBackCDC();
		}

		void STEP() {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "�L�n������", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 200, 20, "Step:" + to_string(step));
			CDDraw::ReleaseBackCDC();
		}
		
		CMovingBitmap candy[10][10];
		CMovingBitmap map[10][10];
		CMovingBitmap unitMap;
		
		int score = 0;
		int step = 10;
		MapLevel maplevel;
		
	private:
		
		
	};
}
//#endif 

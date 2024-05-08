
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

using namespace std;

namespace game_framework {
	class Map {
	public:
		void Build_map() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					map[i][j].LoadBitmapByString({ "resources/CandyLattice.bmp" });
					map[i][j].SetTopLeft(10 + map[0][0].GetWidth()*j, 150 + map[0][0].GetHeight()*i);
					candy[i][j].LoadBitmapByString({"resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp","resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp" }, RGB(255, 255, 255));
					int RandNum = rand() % 6 + 1;		
					candy[i][j].SetFrameIndexOfBitmap(RandNum);
					candy[i][j].SetTopLeft(map[i][j].GetLeft() + (map[i][j].GetWidth() - candy[i][j].GetWidth()) / 2, map[i][j].GetTop() + (map[i][j].GetHeight() - candy[i][j].GetHeight()) / 2);
				}
			}
		}

		void Show_map() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					map[i][j].ShowBitmap();
				}
			}
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					candy[i][j].ShowBitmap();
				}
			}
		}

		void candy_down() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					int k = i;
					if (candy[i][j].GetFrameIndexOfBitmap() == 0) {
						score = score + 10;
						k = i;
						while (1) {
							if (k == 0) {
								int RandNum = rand() % 6 + 1;
								candy[k][j].SetFrameIndexOfBitmap(RandNum);
							}
							else {
								candy[k][j].SetFrameIndexOfBitmap(candy[k - 1][j].GetFrameIndexOfBitmap());
							}
							candy[k][j].SetTopLeft(map[k][j].GetLeft() + (map[k][j].GetWidth() - candy[k][j].GetWidth()) / 2, map[k][j].GetTop() + (map[k][j].GetHeight() - candy[k][j].GetHeight()) / 2);
							k--;
							if (k < 0) {
								break;
							}
						}
					}
				}
			}
		}


		void Candy_Element(int clickX, int clickY, int changeX, int changeY) {
			int i = 0;
			while (1) {
				int j = 0;
				while (1) {
					if (candy[i][j].GetFrameIndexOfBitmap() == 0) {
						j++;
						continue;
					}
					int k_row = j;
					int sum_row = 0;
					while (1) {
						if (isCandySameColor(i, j, i, k_row)) {
							sum_row++;
						}
						else {
							candy_upgrade(clickX, clickY, changeX, changeY, i, j, sum_row, true);
							sum_row = 0;
							break;
						}

						k_row++;
						if (k_row >= 10) {
							candy_upgrade(clickX, clickY, changeX, changeY, i, j, sum_row, true);
							sum_row = 0;
							break;
						}
					}
					int k_col = i;
					int sum_col = 0;
					while (1) {
						if (isCandySameColor(i, j, k_col, j)) {
							sum_col++;
						}
						else {
							candy_upgrade(clickX, clickY, changeX, changeY, i, j, sum_col, false);
							sum_col = 0;
							break;
						}
						k_col++;
						if (k_col >= 10) {
							candy_upgrade(clickX, clickY, changeX, changeY, i, j, sum_col, false);
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
		void candy_change(int i, int j, int x, int y) {
			int num = candy[i][j].GetFrameIndexOfBitmap();
			candy[i][j].SetFrameIndexOfBitmap(candy[x][y].GetFrameIndexOfBitmap());
			candy[x][y].SetFrameIndexOfBitmap(num);
			candy[x][y].SetTopLeft(map[x][y].GetLeft() + (map[x][y].GetWidth() - candy[x][y].GetWidth()) / 2, map[x][y].GetTop() + (map[x][y].GetHeight() - candy[x][y].GetHeight()) / 2);
			candy[i][j].SetTopLeft(map[i][j].GetLeft() + (map[i][j].GetWidth() - candy[i][j].GetWidth()) / 2, map[i][j].GetTop() + (map[i][j].GetHeight() - candy[i][j].GetHeight()) / 2);
			if (candy[i][j].GetFrameIndexOfBitmap() == 25) {
				for (int k = 0; k < 10; k++) {
					for (int z = 0; z < 10; z++) {
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

		void candy_upgrade(int clickX, int clickY, int changeX, int changeY,int i,int j,int sum,bool isRow) {
			/*if (candy[i][j].GetFrameIndexOfBitmap() != candy[clickX][clickY].GetFrameIndexOfBitmap()) {
				clickX = changeX;
				clickY = changeY;
			}*/
			if (isRow) {
				if (sum == 5) {
					for (int z = j; z < j + 5; z++) {
						if ((i == clickX && z == clickY ) || (z == j+2)) {
							for (int k = i; k < i + 3; k++) {
								if (k >= 10) {
									break;
								}
								if (!isCandySameColor(k, z, i, z)) {
									break;
								}
								if (k == i + 2) {
									for (int k1 = i; k1 < i + 3; k1++) {
										//canty_to_empty(k1, z);
										candy[k1][z].SetFrameIndexOfBitmap(0);
									}
								}
							}
							candy[i][z].SetFrameIndexOfBitmap(25);
							continue;
						}
						//canty_to_empty(i,z);
						candy[i][z].SetFrameIndexOfBitmap(0);
					}
				}
				else if (sum == 4) {
					for (int z = j; z < j + 4; z++) {
						if (z == clickY) {
							candy[i][z].SetFrameIndexOfBitmap(8 + (candy[i][z].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						//canty_to_empty(i, z);
						candy[i][z].SetFrameIndexOfBitmap(0);
					}
				}
				
				else if (sum == 3) {	
					for (int k = i; k < i + 3; k++) {
						if (k >= 10) {
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
								candy_skill(i, k1);
								//candy_skill(i, k1);
								//candy[i][k1].SetFrameIndexOfBitmap(0);
							}
				
							for (int k1 = i; k1 < i + 3; k1++) {
								if (k1 == i) {
									continue;
								}
								candy_skill(k1, clickY);
								
								//candy[k1][clickY].SetFrameIndexOfBitmap(0);
							}
							return;
						}					
					}
					
					for (int z = j; z < j + 3; z++) {
						//canty_to_empty(i, z);
						candy_skill(i, z);
						//candy[i][z].SetFrameIndexOfBitmap(0);
					}
				}
			}
			else if(!isRow){
				if (sum == 5) {
					for (int k = j - 2; k < j; k++) {
						if (k < 0 || i + 2 >= 10) {
							break;
						}
						if (!isCandySameColor(i+2, k, i, j)) {
							break;
						}
						if (k == j - 1) {
							for (int k1 = j - 2; k1 < j; k1++) {
								candy_skill(i+2, k1);
								//candy[i + 2][k1].SetFrameIndexOfBitmap(0);
							}
						}
					}
					for (int z = i; z < i + 5; z++) {
						if ((z == clickX && j == clickY) || (z == changeX && j == changeY)) {
							candy[z][j].SetFrameIndexOfBitmap(25);
							continue;
						}
						candy_skill(z, j);
						//candy[z][j].SetFrameIndexOfBitmap(0);
					}
				}
				else if (sum == 4) {
					for (int z = i; z < i + 4; z++) {
						if ((z == clickX && j == clickY) || (z == changeX && j == changeY)) {
							candy[z][j].SetFrameIndexOfBitmap(7 + (candy[z][j].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						candy_skill(z, j);
						//candy[z][j].SetFrameIndexOfBitmap(0);
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
								candy_skill(clickX, k1);
								//candy[clickX][k1].SetFrameIndexOfBitmap(0);
							}

							for (int k1 = i; k1 < i + 3; k1++) {
								if (k1 == clickX) {
									continue;
								}
								candy_skill(k1, j);
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
								candy_skill(clickX, k1);
								//candy[clickX][k1].SetFrameIndexOfBitmap(0);
							}

							for (int k1 = i; k1 < i + 3; k1++) {
								if (k1 == clickX) {
									continue;
								}
								candy_skill(k1, j);
								//candy[k1][j].SetFrameIndexOfBitmap(0);
							}
							return;
						}
					}
					for (int z = i; z < i + 3; z++) {
						candy_skill(z, j);
						//candy[z][j].SetFrameIndexOfBitmap(0);
					}
				}
			}
		}
		
		void candy_skill(int x,int y) {
			//candy_down();
			if (candy[x][y].GetFrameIndexOfBitmap() < 7) {
				candy[x][y].SetFrameIndexOfBitmap(0);
			}
			else if (candy[x][y].GetFrameIndexOfBitmap() == 25) {
				return;
			}
			else if (candy[x][y].GetFrameIndexOfBitmap()%3 == 1 ) {
				for (int i = 0; i < 10; i++) {
					//candy_skill(x, i);
					
					candy[x][i].SetFrameIndexOfBitmap(0);
				}
			}
			else if (candy[x][y].GetFrameIndexOfBitmap() % 3 == 2) {
				for (int i = 0; i < 10; i++) {
					//candy_skill(i, y);
					candy[i][y].SetFrameIndexOfBitmap(0);
				}
			}
			else {
				for (int i = 0; i < 2; i++) {
					if (x - 1 >= 0 && y - 1 >= 0) {
						//candy_skill(x-1, y-1);
						candy[x - 1][y - 1].SetFrameIndexOfBitmap(0);
					}
					if (x - 1 >= 0) {
						//candy_skill(x - 1, y );
						candy[x - 1][y].SetFrameIndexOfBitmap(0);
					}
					if (x - 1 >= 0 && y + 1 < 10) {
						//candy_skill(x - 1, y + 1);
						candy[x - 1][y + 1].SetFrameIndexOfBitmap(0);
					}
					if (y - 1 >= 0) {
						//candy_skill(x , y - 1);
						candy[x][y - 1].SetFrameIndexOfBitmap(0);
					}
					if (y + 1 < 10) {
						//candy_skill(x , y + 1);
						candy[x][y + 1].SetFrameIndexOfBitmap(0);
					}
					if (x + 1 < 10 && y - 1 >= 0) {
						//candy_skill(x + 1, y - 1);
						candy[x + 1][y - 1].SetFrameIndexOfBitmap(0);
					}
					if (x + 1 < 10) {
						//candy_skill(x + 1, y );
						candy[x + 1][y].SetFrameIndexOfBitmap(0);
					}
					if (x + 1 < 10 && y + 1 < 10) {
						candy_skill(x + 1, y + 1);
						//candy[x + 1][y + 1].SetFrameIndexOfBitmap(0);
					}
					candy_down();
					if (x < 9) {
						x = x + 1;
					}

				}
			candy[x][y ].SetFrameIndexOfBitmap(0);
			}
		}
		

		void SCORE() {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC,20, 20, "Score:"+ to_string(score));
			CDDraw::ReleaseBackCDC();
		}

		void STEP() {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 20, "微軟正黑體", RGB(255, 255, 255));
			CTextDraw::Print(pDC, 200, 20, "Step:" + to_string(step));
			CDDraw::ReleaseBackCDC();
		}
		
		CMovingBitmap candy[10][10];
		CMovingBitmap map[10][10];
		int score = 0;
		int step = 10;
		
	
	private:
		
		
	};
}
//#endif 

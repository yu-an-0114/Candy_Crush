
//#ifdef MAP_H
//#define MAP_H
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "blocklevel.h"
#include "effect.h"
#include "MapLevel.h"
#include "levelcheck.h"
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

		void Build_map(int level) {
			unitMap.LoadBitmapByString({ "resources/CandyLattice.bmp" });
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (maplevel.mapLevel[level][i][j] == 0) {
						continue;
					}
					else {
						map[i][j].LoadBitmapByString({ "resources/CandyLattice.bmp" });
						map[i][j].SetTopLeft(10 + unitMap.GetWidth()*j, 150 + unitMap.GetHeight()*i);
						candy[i][j].LoadBitmapByString({ "resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp","resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp" }, RGB(255, 255, 255));
						candy[i][j].SetTopLeft(map[i][j].GetLeft() + (unitMap.GetWidth() - candy[i][j].GetWidth()) / 2, map[i][j].GetTop() + (unitMap.GetHeight() - candy[i][j].GetHeight()) / 2);
						candy[i][j].SetFrameIndexOfBitmap(0);
						cherry[i][j].LoadBitmapByString({ "resources/cherry.bmp" }, RGB(255, 255, 255));
						cherry[i][j].SetTopLeft(map[i][j].GetLeft() + (unitMap.GetWidth() - cherry[i][j].GetWidth()) / 2, map[i][j].GetTop() + (unitMap.GetHeight() - cherry[i][j].GetHeight()) / 2);
						cherry[i][j].SetFrameIndexOfBitmap(0);
						obstacle[i][j].LoadBitmapByString({ "resources/block/X_block.bmp","resources/block/black_block.bmp","resources/block/sugar.bmp","resources/block/sugar2.bmp","resources/block/sugar3.bmp","resources/block/sugar4.bmp","resources/block/sugar5.bmp","resources/block/chocolate_machine.bmp","resources/block/chocolate.bmp" ,"resources/block/glass.bmp","resources/block/glass2.bmp" }, RGB(255, 255, 255));
						obstacle[i][j].SetTopLeft(map[i][j].GetLeft() + (unitMap.GetWidth() - obstacle[i][j].GetWidth()) / 2, map[i][j].GetTop() + (unitMap.GetHeight() - obstacle[i][j].GetHeight()) / 2);
						obstacle[i][j].SetFrameIndexOfBitmap(0);
						bomb[i][j].LoadBitmapByString({ "resources/candy/white.bmp","resources/bomb/yellow-bomb.bmp","resources/bomb/blue-bomb.bmp" ,"resources/bomb/red-bomb.bmp" ,"resources/bomb/purple-bomb.bmp" ,"resources/bomb/green-bomb.bmp" ,"resources/bomb/orange-bomb.bmp" }, RGB(255, 255, 255));
						bomb[i][j].SetTopLeft(map[i][j].GetLeft() + (unitMap.GetWidth() - bomb[i][j].GetWidth()) / 2, map[i][j].GetTop() + (unitMap.GetHeight() - bomb[i][j].GetHeight()) / 2);
						effect[i][j].LoadBitmapByString({ "resources/special_effect/effect1.bmp" ,"resources/special_effect/effect2.bmp" ,"resources/special_effect/effect3.bmp" ,"resources/special_effect/effect4.bmp" ,"resources/special_effect/effect5.bmp","resources/special_effect/effect_base.bmp" }, RGB(255, 255, 255));
						effect[i][j].SetTopLeft(map[i][j].GetLeft(), map[i][j].GetTop());
						effect[i][j].SetAnimation(1000, true);
						if (maplevel.mapLevel[level][i][j] == 1) {
							int RandNum = rand() % 6 + 1;
							candy[i][j].SetFrameIndexOfBitmap(RandNum);
						}
						else if (maplevel.mapLevel[level][i][j] == 2) {
							int RandNum = rand() % 6 + 1;
							candy[i][j].SetFrameIndexOfBitmap(RandNum);
							obstacle[i][j].SetFrameIndexOfBitmap(0);
						}
						else if (maplevel.mapLevel[level][i][j] == 3) {
							cherry[i][j].SetFrameIndexOfBitmap(0);
						}
						else if (maplevel.mapLevel[level][i][j] == 4) {
							int RandNum = rand() % 6 + 1;
							bomb[i][j].SetFrameIndexOfBitmap(RandNum);
						}

						else if (maplevel.mapLevel[level][i][j] == 5) {
							obstacle[i][j].SetFrameIndexOfBitmap(7);
						}
						else if (maplevel.mapLevel[level][i][j] == 6) {
							obstacle[i][j].SetFrameIndexOfBitmap(8);
						}
						else if (maplevel.mapLevel[level][i][j] == 7) {
							obstacle[i][j].SetFrameIndexOfBitmap(2);
						}
						else if (maplevel.mapLevel[level][i][j] == 8) {
							obstacle[i][j].SetFrameIndexOfBitmap(3);
						}
						else if (maplevel.mapLevel[level][i][j] == 9) {
							obstacle[i][j].SetFrameIndexOfBitmap(4);
						}
						else if (maplevel.mapLevel[level][i][j] == 10) {
							obstacle[i][j].SetFrameIndexOfBitmap(5);
						}
						else if (maplevel.mapLevel[level][i][j] == 11) {
							obstacle[i][j].SetFrameIndexOfBitmap(6);
						}
						else if (maplevel.mapLevel[level][i][j] == 12) {
							int RandNum = rand() % 6 + 1;
							candy[i][j].SetFrameIndexOfBitmap(RandNum);
							obstacle[i][j].SetFrameIndexOfBitmap(9);
						}
						else if (maplevel.mapLevel[level][i][j] == 13) {
							int RandNum = rand() % 6 + 1;
							candy[i][j].SetFrameIndexOfBitmap(RandNum);
							obstacle[i][j].SetFrameIndexOfBitmap(10);
						}
					}
				}
			}
			helper.stepInit(LevelCheck::rank);
		}


		void Show_effect(int level) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (maplevel.mapLevel[level][i][j] == 1) {

						if (effectlevel.effect[i][j] == 1) {

							effect[i][j].ShowBitmap();
							//effect[i][j].ToggleAnimation();
							time.Delay(10);

						}
						else if (effectlevel.effect[i][j] == 2) {
								effect[i][j].SetFrameIndexOfBitmap(5);
								//effect[i][j].SetFrameIndexOfBitmap(3);
								effect[i][j].ShowBitmap();
								effect[i][j].ToggleAnimation();
								time.Delay(5);
							
						}
						effectlevel.Unshine(i, j);
					}

				
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
					else {
						if (maplevel.mapLevel[level][i][j] == 1) {
							candy[i][j].ShowBitmap();
						}
						else {
							candy[i][j].UnshowBitmap();
						}

						if (maplevel.mapLevel[level][i][j] == 2) {
							candy[i][j].ShowBitmap();
							obstacle[i][j].ShowBitmap();

						}
						else {
							candy[i][j].UnshowBitmap();
							obstacle[i][j].UnshowBitmap();
						}
						if (maplevel.mapLevel[level][i][j] == 3) {
							cherry[i][j].ShowBitmap();

						}
						else {
							cherry[i][j].UnshowBitmap();
						}
						if (maplevel.mapLevel[level][i][j] == 4) {
							bomb[i][j].ShowBitmap();

						}
						else {
							bomb[i][j].UnshowBitmap();
						}

						if (maplevel.mapLevel[level][i][j] == 5) {
							obstacle[i][j].ShowBitmap();

						}
						else {
							obstacle[i][j].UnshowBitmap();
						}
						if (maplevel.mapLevel[level][i][j] == 6) {
							obstacle[i][j].ShowBitmap();

						}
						else {
							obstacle[i][j].UnshowBitmap();
						}
						if (maplevel.mapLevel[level][i][j] == 7) {
							obstacle[i][j].ShowBitmap();

						}
						else {
							obstacle[i][j].UnshowBitmap();
						}
						if (maplevel.mapLevel[level][i][j] == 8) {
							obstacle[i][j].ShowBitmap();

						}
						else {
							obstacle[i][j].UnshowBitmap();
						}
						if (maplevel.mapLevel[level][i][j] == 9) {
							obstacle[i][j].ShowBitmap();

						}
						else {
							obstacle[i][j].UnshowBitmap();
						}
						if (maplevel.mapLevel[level][i][j] == 10) {
							obstacle[i][j].ShowBitmap();

						}
						else {
							obstacle[i][j].UnshowBitmap();
						}
						if (maplevel.mapLevel[level][i][j] == 11) {
							obstacle[i][j].ShowBitmap();

						}
						else {
							obstacle[i][j].UnshowBitmap();
						}
						if (maplevel.mapLevel[level][i][j] == 12) {
							obstacle[i][j].ShowBitmap();
							candy[i][j].ShowBitmap();
						}
						else {
							obstacle[i][j].UnshowBitmap();
							candy[i][j].UnshowBitmap();
						}
						if (maplevel.mapLevel[level][i][j] == 13) {
							obstacle[i][j].ShowBitmap();
							candy[i][j].ShowBitmap();

						}
						else {
							obstacle[i][j].UnshowBitmap();
							candy[i][j].UnshowBitmap();
						}
					}
				}
			}
		}
		int search_up_can_down(int x, int y, int level) {
			int j = y;
			for (int i = x - 1; i >= 0; i--) {
				if (i < 0) {
					break;
				}
				if (maplevel.mapLevel[level][i][j] == 0) {
					continue;
				}
				if (maplevel.mapLevel[level][i][j] == 1 && candy[i][j].GetFrameIndexOfBitmap() == 0) {
					continue;
				}

				if (maplevel.mapLevel[level][i][j] == 2 || (5 <= maplevel.mapLevel[level][i][j] && maplevel.mapLevel[level][i][j] <= 11)) {
					return -1;
				}
				else if ((maplevel.mapLevel[level][i][j] == 1 && candy[i][j].GetFrameIndexOfBitmap() != 0) || maplevel.mapLevel[level][i][j] == 3 || maplevel.mapLevel[level][i][j] == 4 || maplevel.mapLevel[level][i][j] == 12 || maplevel.mapLevel[level][i][j] == 13) {
					return i;
				}
				if (i == 0) {
					return -2;
				}
			}
			return -1;
		}

		bool is_candy_down(int x, int y, int level) {
			for (int i = x - 1; i >= 0; i--) {
				if (i < 0) {
					break;
				}
				if (maplevel.mapLevel[level][i][y] == 0) {
					continue;
				}
				if (maplevel.mapLevel[level][i][y] == 1 && candy[i][y].GetFrameIndexOfBitmap() == 0) {
					continue;
				}
				if ((maplevel.mapLevel[level][i][y] == 1 && candy[i][y].GetFrameIndexOfBitmap() != 0) || maplevel.mapLevel[level][i][y] == 3 || maplevel.mapLevel[level][i][y] == 4 || maplevel.mapLevel[level][i][y] == 12 || maplevel.mapLevel[level][i][y] == 13) {
					return true;
				}
				else {
					return false;
				}
			}
			return false;
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
						LevelCheck::score = LevelCheck::score + 10;
						k = i;
						while (1) {
							if (k < Map_level_lattice_top_not_empty_num(j, level)) {
								break;
							}
							if (maplevel.mapLevel[level][k][j] == 0) {
								k--;
								candyLatticeEmpty++;
								continue;
							}
							if (k == Map_level_lattice_top_not_empty_num(j, level)) {

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
		int top_random(int row, int col, int level) {
			for (int i = row; i >= 0; i--) {
				if (maplevel.mapLevel[level][i][col] == 0) {
					return row;
				}
			}
			return -1;
		}

		void candy_special_and_special(int clickX, int clickY, int changeX, int changeY, int level) {
			if (candy[clickX][clickY].GetFrameIndexOfBitmap() > 6 && candy[changeX][changeY].GetFrameIndexOfBitmap() > 6) {
				if (candy[clickX][clickY].GetFrameIndexOfBitmap() == 25 && candy[changeX][changeY].GetFrameIndexOfBitmap() == 25) {
					for (int k = 0; k < 10; k++) {
						for (int k1 = 0; k1 < 10; k1++) {
							if (maplevel.mapLevel[level][k][k1] == 0) {
								continue;
							}
							candy_skill(k, k1, level);
						}
					}
				}
				else if ((candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 == 0 && (candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 == 0) {
					for (int t = 0; t < 2; t++) {
						for (int k = clickX - 2; k <= clickX + 2; k++) {
							for (int k1 = clickY - 2; k1 <= clickY + 2; k1++) {
								if (k < 0 || k > 9 || k1 < 0 || k1 > 9) {
									continue;
								}
								if (maplevel.mapLevel[level][k][k1] == 0) {
									continue;
								}
								candy_skill(k, k1, level);
							}
						}
					}
				}
				else if (((candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 == 0 && (candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 != 0) || ((candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 != 0 && (candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 == 0)) {
					for (int k = clickX - 1; k <= clickX + 1; k++) {
						for (int k1 = 0; k1 < 10; k1++) {
							if (k < 0 || k > 9 || k1 < 0 || k1 > 9) {
								continue;
							}
							if (maplevel.mapLevel[level][k][k1] == 0) {
								continue;
							}
							candy_skill(k, k1, level);
						}
					}
					for (int k = clickY - 1; k <= clickY + 1; k++) {
						if (k < 0 || k > 9) {
							continue;
						}
						for (int k1 = 0; k1 < 10; k1++) {
							if (maplevel.mapLevel[level][k1][k] == 0) {
								continue;
							}
							candy_skill(k, k1, level);
						}
					}
				}
				else if ((candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 != 0 && (candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 != 0) {
					for (int k = 0; k < 10; k++) {
						if (maplevel.mapLevel[level][clickX][k] != 0) {
							candy_skill(clickX, k, level);
						}

						if (maplevel.mapLevel[level][k][clickY] != 0) {
							candy_skill(k, clickY, level);
						}
					}
				}
			}
		}

		int Candy_Connet(int x, int y, bool checkRow, int level) {
			int x1 = x;
			int y1 = y;
			int sum = 0;
			if (checkRow) {
				while (1) {
					if (maplevel.mapLevel[level][x1][y1] == 0) {
						break;
					}
					if (!isCandySameColor(x, y, x1, y1)) {
						break;
					}
					sum++;
					y1++;
					if (y1 == 10) {
						y1 = 9;
						break;
					}
				}
				return sum;
			}
			else {
				while (1) {
					if (maplevel.mapLevel[level][x1][y1] == 0) {
						break;
					}

					if (!isCandySameColor(x, y, x1, y1)) {
						break;
					}
					x1++;
					sum++;
					if (x1 == 10) {
						x1 = 9;
						break;
					}
				}
				return sum;
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
					if (candy[i][j].GetFrameIndexOfBitmap() == 0) {
						j++;
						continue;
					}
					int k_row = j;
					int sum_row = 0;
					candy_special_and_special(clickX, clickY, changeX, changeY, level);
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
				if (candy[x][y].GetFrameIndexOfBitmap() % 3 == 0) {
					color_num2 = (int)ceil((candy[x][y].GetFrameIndexOfBitmap() - 6) / 3);
				}
				else {
					color_num2 = (int)ceil((candy[x][y].GetFrameIndexOfBitmap() - 6) / 3) + 1;
				}
			}
			else {
				color_num2 = candy[x][y].GetFrameIndexOfBitmap();
			}
			return color_num == color_num2;
		}
		void candy_change(int i, int j, int x, int y, int level) {
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
							effectlevel.shine(k, z, 2);
						}
					}
				}
				candy[i][j].SetFrameIndexOfBitmap(0);
				effectlevel.shine(i, j);
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
							effectlevel.shine(k, z);
						}
					}
				}
				candy[x][y].SetFrameIndexOfBitmap(0);
				effectlevel.shine(x, y);
			}
		}
		void candy_upgrade(int clickX, int clickY, int changeX, int changeY, int i, int j, int sum, bool isRow, int level) {
			if (isRow) {
				if (sum == 5) {
					for (int k = j; k < j + sum; k++) {
						if (maplevel.mapLevel[level][i][k] == 2) {
							maplevel.mapLevel[level][i][k] = 1;
						}
						if (k == j + 2) {
							if (Candy_Connet(i, k, false, level) >= 3) {
								for (int k1 = i + 1; k1 < i + Candy_Connet(i, k, false, level); k1++) {
									candy_skill(k1, k, level);
								}
							}
							candy[i][k].SetFrameIndexOfBitmap(25);
						}
						else {
							candy_skill(i, k, level);
						}
					}
				}
				else if (sum == 4) {
					for (int k = j; k < j + sum; k++) {

						bool hasCandyPack = false;
						if (Candy_Connet(i, k, false, level) >= 3) {
							hasCandyPack = true;
							for (int k1 = i + 1; k1 < i + Candy_Connet(i, k, false, level); k1++) {
								candy_skill(k1, k, level);
							}
							candy[i][k].SetFrameIndexOfBitmap(9 + (candy[i][k].GetFrameIndexOfBitmap() - 1) * 3);
						}
						if (k == j + sum - 1 && !hasCandyPack) {
							candy[i][clickY].SetFrameIndexOfBitmap(8 + (candy[i][k].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						candy_skill(i, k, level);
					}
				}
				else if (sum == 3) {
					for (int k = j; k < j + sum; k++) {
						if (Candy_Connet(i, k, false, level) >= 3) {
							candy[i][k].SetFrameIndexOfBitmap(9 + (candy[i][k].GetFrameIndexOfBitmap() - 1) * 3);
							for (int k1 = i + 1; k1 < i + Candy_Connet(i, k, false, level) + 2; k1++) {
								int a = 1;
								candy_skill(k1, k, level);
							}
						}
						else {
							candy_skill(i, k, level);
						}
					}
				}
			}
			else if (!isRow) {
				if (sum == 5) {

					for (int k = i; k < i + sum; k++) {
						if (k == i + 2) {
							if (Candy_Connet(k, j, true, level) >= 3) {
								for (int k1 = j + 1; k1 < j + Candy_Connet(k, j, true, level); k1++) {
									candy_skill(k, k1, level);
								}
							}
							candy[k][j].SetFrameIndexOfBitmap(25);
						}
						else {
							candy_skill(k, j, level);
						}
					}
				}
				else if (sum == 4) {

					for (int k = i; k < i + sum; k++) {
						bool hasCandyPack = false;
						if (Candy_Connet(k, j, true, level) >= 3) {
							hasCandyPack = true;
							for (int k1 = j + 1; k1 < j + Candy_Connet(k, j, true, level); k1++) {
								candy_skill(k, k1, level);
							}
							candy[k][j].SetFrameIndexOfBitmap(9 + (candy[k][j].GetFrameIndexOfBitmap() - 1) * 3);
						}
						if (k == i + sum - 1 && !hasCandyPack) {
							candy[k][j].SetFrameIndexOfBitmap(8 + (candy[k][j].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						candy_skill(k, j, level);
					}
				}
				else if (sum == 3) {
					for (int k = i; k < i + sum; k++) {
						if (Candy_Connet(k, j, true, level) >= 3) {
							for (int k1 = j + 1; j < j + Candy_Connet(k, j, true, level); k1++) {
								candy_skill(k, k1, level);
							}
							candy[k][j].SetFrameIndexOfBitmap(9 + (candy[k][j].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						candy_skill(k, j, level);
					}
				}
			}

		}

		void candy_skill(int x, int y, int level) {
			if (maplevel.mapLevel[level][x][y] == 0) {
				return;
			}
			if (maplevel.mapLevel[level][x][y] == 2) {
				maplevel.mapLevel[level][x][y] = 1;
			}
			if (candy[x][y].GetFrameIndexOfBitmap() < 7) {
				candy[x][y].SetFrameIndexOfBitmap(0);
				effectlevel.shine(x, y);
			}
			else if (candy[x][y].GetFrameIndexOfBitmap() == 25) {
				return;
			}
			else if (candy[x][y].GetFrameIndexOfBitmap() % 3 == 1) {
				for (int i = 0; i < 10; i++) {
					if (maplevel.mapLevel[level][x][i] == 0) {
						continue;
					}
					candy[x][i].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x, i);
				}
			}
			else if (candy[x][y].GetFrameIndexOfBitmap() % 3 == 2) {
				for (int i = 0; i < 10; i++) {
					if (maplevel.mapLevel[level][i][y] == 0) {
						continue;
					}
					candy[i][y].SetFrameIndexOfBitmap(0);
					effectlevel.shine(i, y);
				}
			}
			else {
				for (int i = 0; i < 2; i++) {
					if (x - 1 >= 0 && y - 1 >= 0) {
						if (maplevel.mapLevel[level][x - 1][y - 1] == 1) {
							candy[x - 1][y - 1].SetFrameIndexOfBitmap(0);
							effectlevel.shine(x-1, y-1);
						}
					}
					if (x - 1 >= 0) {
						if (maplevel.mapLevel[level][x - 1][y] == 1) {
							candy[x - 1][y].SetFrameIndexOfBitmap(0);
							effectlevel.shine(x-1, y);
						}
					}
					if (x - 1 >= 0 && y + 1 < 10) {
						if (maplevel.mapLevel[level][x - 1][y + 1] == 1) {
							candy[x - 1][y + 1].SetFrameIndexOfBitmap(0);
							effectlevel.shine(x-1, y+1);
						}
					}
					if (y - 1 >= 0) {
						if (maplevel.mapLevel[level][x][y - 1] == 1) {
							candy[x][y - 1].SetFrameIndexOfBitmap(0);
							effectlevel.shine(x, y-1);
						}
					}
					if (y + 1 < 10) {
						if (maplevel.mapLevel[level][x][y + 1] == 1) {
							candy[x][y + 1].SetFrameIndexOfBitmap(0);
							effectlevel.shine(x, y+1);
						}
					}
					if (x + 1 < 10 && y - 1 >= 0) {
						if (maplevel.mapLevel[level][x + 1][y - 1] == 1) {
							candy[x + 1][y - 1].SetFrameIndexOfBitmap(0);
							effectlevel.shine(x+1, y-1);
						}
					}
					if (x + 1 < 10) {
						if (maplevel.mapLevel[level][x + 1][y] == 1) {
							candy[x + 1][y].SetFrameIndexOfBitmap(0);
							effectlevel.shine(x+1, y);
						}
					}
					if (x + 1 < 10 && y + 1 < 10) {
						if (maplevel.mapLevel[level][x + 1][y + 1] == 1) {
							candy[x + 1][y + 1].SetFrameIndexOfBitmap(0);
							effectlevel.shine(x+1, y+1);
						}
					}
					candy_down(level);
					if (x < 9) {
						x = x + 1;
					}
				}
				candy[x][y].SetFrameIndexOfBitmap(0);
				effectlevel.shine(x, y);
			}
		}
		
		void different_game_play(int level) {
			if (0 <= level && level <= 4) {

			}
			else if (5 <= level && level <= 9) {

			}
			else if (10 <= level && level <= 14) {

			}
			else if (15 <= level && level <= 19) {

			}
			else if (20 <= level && level <= 24) {

			}
			else if (25 <= level && level <= 29) {

			}
		}

		void win_game_condition(int level) {
			if (0 <= level && level <= 4) {

			}
			else if (5 <= level && level <= 9) {

			}
			else if (10 <= level && level <= 14) {

			}
			else if (15 <= level && level <= 19) {

			}
			else if (20 <= level && level <= 24) {

			}
			else if (25 <= level && level <= 29) {

			}
		}
		
		

		int Map_level_lattice_top_not_empty_num(int col, int level) {
			for (int i = 0; i < 10; i++) {
				if (maplevel.mapLevel[level][i][col] != 0) {
					return i;
				}
			}
			return 0;
		}
		


		CMovingBitmap cherry[10][10];
		CMovingBitmap candy[10][10];
		CMovingBitmap map[10][10];
		CMovingBitmap block[10][10];
		CMovingBitmap effect[10][10];
		CMovingBitmap unitMap;
		CMovingBitmap bomb[10][10];
		CMovingBitmap obstacle[10][10];

		CSpecialEffect time;
		MapLevel maplevel;
		BlockLevel blocklevel;
		Effect effectlevel;
		LevelCheck helper;

	private:
		
		
	};
}
//#endif 

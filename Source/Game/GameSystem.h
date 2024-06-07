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
#include <typeinfo>
#include "Map.h"
#include "UI.h"
using namespace std;

namespace game_framework {
	class GameSystem {
	public:

		int search_up_can_down(int x, int y, int level) {
			int j = y;
			for (int i = x - 1; i >= 0; i--) {
				if (i < 0) {
					break;
				}
				if (map_level[level][i][j] == 0) {
					continue;
				}
				if (map_level[level][i][j] == 1 && map.candy[i][j].GetFrameIndexOfBitmap() == 0) {
					continue;
				}

				if (map_level[level][i][j] == 2 || (5 <= map_level[level][i][j] && map_level[level][i][j] <= 11)) {
					return -1;
				}
				else if ((map_level[level][i][j] == 1 && map.candy[i][j].GetFrameIndexOfBitmap() != 0) || map_level[level][i][j] == 3 || map_level[level][i][j] == 4 || map_level[level][i][j] == 12 || map_level[level][i][j] == 13) {
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
				if (map_level[level][i][y] == 0) {
					continue;
				}
				if (map_level[level][i][y] == 1 && map.candy[i][y].GetFrameIndexOfBitmap() == 0) {
					continue;
				}
				if ((map_level[level][i][y] == 1 && map.candy[i][y].GetFrameIndexOfBitmap() != 0) || map_level[level][i][y] == 3 || map_level[level][i][y] == 4 || map_level[level][i][y] == 12 || map_level[level][i][y] == 13) {
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
					if (map_level[level][i][j] == 0) {
						continue;
					}
					int k = i;
					if (map.candy[i][j].GetFrameIndexOfBitmap() == 0) {
						k = i;
						while (1) {
							/*
							if (k < Map_level_lattice_top_not_empty_num(j, level)) {
								break;
							}*/
							if (map_level[level][k][j] == 0) {
								k--;
								candyLatticeEmpty++;
								continue;
							}
							/*
							if (k == Map_level_lattice_top_not_empty_num(j, level)) {

								int RandNum = rand() % 6 + 1;
								map.candy[k][j].SetFrameIndexOfBitmap(RandNum);
							}*/
							else {
								map.candy[k][j].SetFrameIndexOfBitmap(map.candy[k - candyLatticeEmpty - 1][j].GetFrameIndexOfBitmap());
							}
							map.set_candy_lattice_center(k, j, map.candy);
							k--;
						}
					}
				}
			}
		}
		int top_random(int row, int col, int level) {
			for (int i = row; i >= 0; i--) {
				if (map_level[level][i][col] == 0) {
					return row;
				}
			}
			return -1;
		}

		void candy_special_and_special(int clickX, int clickY, int changeX, int changeY, int level) {
			if (map.candy[clickX][clickY].GetFrameIndexOfBitmap() > 6 && map.candy[changeX][changeY].GetFrameIndexOfBitmap() > 6) {
				if (map.candy[clickX][clickY].GetFrameIndexOfBitmap() == 25 && map.candy[changeX][changeY].GetFrameIndexOfBitmap() == 25) {
					for (int k = 0; k < 10; k++) {
						for (int k1 = 0; k1 < 10; k1++) {
							if (map_level[level][k][k1] == 0) {
								continue;
							}
							candy_skill(k, k1, level);
						}
					}
				}
				else if ((map.candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 == 0 && (map.candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 == 0) {
					for (int t = 0; t < 2; t++) {
						for (int k = clickX - 2; k <= clickX + 2; k++) {
							for (int k1 = clickY - 2; k1 <= clickY + 2; k1++) {
								if (k < 0 || k > 9 || k1 < 0 || k1 > 9) {
									continue;
								}
								if (map_level[level][k][k1] == 0) {
									continue;
								}
								candy_skill(k, k1, level);
							}
						}
					}
				}
				else if (((map.candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 == 0 && (map.candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 != 0) || ((map.candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 != 0 && (map.candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 == 0)) {
					for (int k = clickX - 1; k <= clickX + 1; k++) {
						for (int k1 = 0; k1 < 10; k1++) {
							if (k < 0 || k > 9 || k1 < 0 || k1 > 9) {
								continue;
							}
							if (map_level[level][k][k1] == 0) {
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
							if (map_level[level][k1][k] == 0) {
								continue;
							}
							candy_skill(k, k1, level);
						}
					}
				}
				else if ((map.candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 != 0 && (map.candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 != 0) {
					for (int k = 0; k < 10; k++) {
						if (map_level[level][clickX][k] != 0) {
							candy_skill(clickX, k, level);
						}

						if (map_level[level][k][clickY] != 0) {
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
					if (map_level[level][x1][y1] == 0) {
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
					if (map_level[level][x1][y1] == 0) {
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
					if (map_level[level][i][j] == 0) {
						j++;
						continue;
					}
					if (map.candy[i][j].GetFrameIndexOfBitmap() == 0) {
						j++;
						continue;
					}
					int k_row = j;
					int sum_row = 0;
					candy_special_and_special(clickX, clickY, changeX, changeY, level);
					while (1) {
						if (map_level[level][i][k_row] == 0) {
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
						if (map_level[level][i][k_col] == 0) {
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
			if (map.candy[i][j].GetFrameIndexOfBitmap() == 25 || map.candy[x][y].GetFrameIndexOfBitmap() == 25) {
				return false;
			}
			if (map.candy[i][j].GetFrameIndexOfBitmap() > 6) {
				if (map.candy[i][j].GetFrameIndexOfBitmap() % 3 == 0) {
					color_num = (int)ceil((map.candy[i][j].GetFrameIndexOfBitmap() - 6) / 3);
				}
				else {
					color_num = (int)ceil((map.candy[i][j].GetFrameIndexOfBitmap() - 6) / 3) + 1;
				}
			}
			else {
				color_num = map.candy[i][j].GetFrameIndexOfBitmap();
			}
			if (map.candy[x][y].GetFrameIndexOfBitmap() > 6) {
				if (map.candy[x][y].GetFrameIndexOfBitmap() % 3 == 0) {
					color_num2 = (int)ceil((map.candy[x][y].GetFrameIndexOfBitmap() - 6) / 3);
				}
				else {
					color_num2 = (int)ceil((map.candy[x][y].GetFrameIndexOfBitmap() - 6) / 3) + 1;
				}
			}
			else {
				color_num2 = map.candy[x][y].GetFrameIndexOfBitmap();
			}
			return color_num == color_num2;
		}
		void candy_change(int i, int j, int x, int y, int level) {
			int num = map.candy[i][j].GetFrameIndexOfBitmap();
			map.candy[i][j].SetFrameIndexOfBitmap(map.candy[x][y].GetFrameIndexOfBitmap());
			map.candy[x][y].SetFrameIndexOfBitmap(num);
			map.set_candy_lattice_center(i, j, map.candy);
			map.set_candy_lattice_center(x, y, map.candy);
			if (map.candy[i][j].GetFrameIndexOfBitmap() == 25) {
				for (int k = 0; k < 10; k++) {
					for (int z = 0; z < 10; z++) {
						if (map_level[level][k][z] == 0) {
							continue;
						}
						if (k == x && z == y) {
							continue;
						}
						if (map.candy[k][z].GetFrameIndexOfBitmap() == map.candy[x][y].GetFrameIndexOfBitmap()) {
							map.candy[k][z].SetFrameIndexOfBitmap(0);
						}
					}
				}
				map.candy[i][j].SetFrameIndexOfBitmap(0);
			}
			else if (map.candy[x][y].GetFrameIndexOfBitmap() == 25) {
				for (int k = 0; k < 10; k++) {
					for (int z = 0; z < 10; z++) {
						if (map_level[level][k][z] == 0) {
							continue;
						}
						if (k == i && z == j) {
							continue;
						}
						if (map.candy[k][z].GetFrameIndexOfBitmap() == map.candy[i][j].GetFrameIndexOfBitmap()) {
							map.candy[k][z].SetFrameIndexOfBitmap(0);
						}
					}
				}
				map.candy[x][y].SetFrameIndexOfBitmap(0);
			}
		}
		void candy_upgrade(int clickX, int clickY, int changeX, int changeY, int i, int j, int sum, bool isRow, int level) {
			if (isRow) {
				if (sum == 5) {
					for (int k = j; k < j + sum; k++) {
						if (map_level[level][i][k] == 2) {
							map_level[level][i][k] = 1;
						}
						if (k == j + 2) {
							if (Candy_Connet(i, k, false, level) >= 3) {
								for (int k1 = i + 1; k1 < i + Candy_Connet(i, k, false, level); k1++) {
									candy_skill(k1, k, level);
								}
							}
							map.candy[i][k].SetFrameIndexOfBitmap(25);
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
							map.candy[i][k].SetFrameIndexOfBitmap(9 + (map.candy[i][k].GetFrameIndexOfBitmap() - 1) * 3);
						}
						if (k == j + sum - 1 && !hasCandyPack) {
							map.candy[i][clickY].SetFrameIndexOfBitmap(8 + (map.candy[i][k].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						candy_skill(i, k, level);
					}
				}
				else if (sum == 3) {
					for (int k = j; k < j + sum; k++) {
						if (Candy_Connet(i, k, false, level) >= 3) {
							map.candy[i][k].SetFrameIndexOfBitmap(9 + (map.candy[i][k].GetFrameIndexOfBitmap() - 1) * 3);
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
							map.candy[k][j].SetFrameIndexOfBitmap(25);
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
							map.candy[k][j].SetFrameIndexOfBitmap(9 + (map.candy[k][j].GetFrameIndexOfBitmap() - 1) * 3);
						}
						if (k == i + sum - 1 && !hasCandyPack) {
							map.candy[k][j].SetFrameIndexOfBitmap(8 + (map.candy[k][j].GetFrameIndexOfBitmap() - 1) * 3);
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
							map.candy[k][j].SetFrameIndexOfBitmap(9 + (map.candy[k][j].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						candy_skill(k, j, level);
					}
				}
			}

		}

		void candy_skill(int x, int y, int level) {
			if (map_level[level][x][y] == 0) {
				return;
			}
			if (map_level[level][x][y] == 2) {
				map_level[level][x][y] = 1;
			}
			if (map.candy[x][y].GetFrameIndexOfBitmap() < 7) {
				map.candy[x][y].SetFrameIndexOfBitmap(0);
			}
			else if (map.candy[x][y].GetFrameIndexOfBitmap() == 25) {
				return;
			}
			else if (map.candy[x][y].GetFrameIndexOfBitmap() % 3 == 1) {
				for (int i = 0; i < 10; i++) {
					if (map_level[level][x][i] == 0) {
						continue;
					}
					map.candy[x][i].SetFrameIndexOfBitmap(0);
				}
			}
			else if (map.candy[x][y].GetFrameIndexOfBitmap() % 3 == 2) {
				for (int i = 0; i < 10; i++) {
					if (map_level[level][i][y] == 0) {
						continue;
					}
					map.candy[i][y].SetFrameIndexOfBitmap(0);
				}
			}
			else {
				for (int i = 0; i < 2; i++) {
					if (x - 1 >= 0 && y - 1 >= 0) {
						if (map_level[level][x - 1][y - 1] == 1) {
							map.candy[x - 1][y - 1].SetFrameIndexOfBitmap(0);
						}
					}
					if (x - 1 >= 0) {
						if (map_level[level][x - 1][y] == 1) {
							map.candy[x - 1][y].SetFrameIndexOfBitmap(0);
						}
					}
					if (x - 1 >= 0 && y + 1 < 10) {
						if (map_level[level][x - 1][y + 1] == 1) {
							map.candy[x - 1][y + 1].SetFrameIndexOfBitmap(0);
						}
					}
					if (y - 1 >= 0) {
						if (map_level[level][x][y - 1] == 1) {
							map.candy[x][y - 1].SetFrameIndexOfBitmap(0);
						}
					}
					if (y + 1 < 10) {
						if (map_level[level][x][y + 1] == 1) {
							map.candy[x][y + 1].SetFrameIndexOfBitmap(0);
						}
					}
					if (x + 1 < 10 && y - 1 >= 0) {
						if (map_level[level][x + 1][y - 1] == 1) {
							map.candy[x + 1][y - 1].SetFrameIndexOfBitmap(0);
						}
					}
					if (x + 1 < 10) {
						if (map_level[level][x + 1][y] == 1) {
							map.candy[x + 1][y].SetFrameIndexOfBitmap(0);
						}
					}
					if (x + 1 < 10 && y + 1 < 10) {
						if (map_level[level][x + 1][y + 1] == 1) {
							map.candy[x + 1][y + 1].SetFrameIndexOfBitmap(0);
						}
					}
					candy_down(level);
					if (x < 9) {
						x = x + 1;
					}
				}
				map.candy[x][y].SetFrameIndexOfBitmap(0);
			}
		}

		Map map;
		UI Ui;
		bool mouse_candy_state = false;
		CPoint candy_start;
		int num = 0;
		int clickX = 0;
		int clickY = 0;
		int changeX = 0;
		int changeY = 0;
		bool canMove = true;
	};
}


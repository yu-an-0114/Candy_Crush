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
		int search_up_can_down(int x, int col, int level) {
			for (int i = x - 1; i >= top_random(x, col, level); i--) {
				if (map.candy[i][col].is_candy_empty(level, i, col, map.candy)) {
					continue;
				}
				if (map_level[level][i][col] == 1 || map_level[level][i][col] == 3 || map_level[level][i][col] == 4 || map_level[level][i][col] == 12 || map_level[level][i][col] == 13) {
					return i;
				}
				if (map_level[level][i][col] == 2 || (5 <= map_level[level][i][col] && map_level[level][i][col] <= 11)) {
					return -1;
				}
			}
			return -1;
		}
		int search_up_can_down_type(int x, int y, int level) {
			return map_level[level][search_up_can_down(x, y, level)][y];
		}
		/*bool is_candy_down(int x, int y, int level) {
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
		}*/
		
		void object_down(int level) {
			for (int j = 0; j < 10; j++) {
				for (int i = 9; i >= 0; i--) {
					if (map.candy[i][j].is_candy_empty(level, i, j,map.candy) || ((map_level[level][i][j] == 12 || map_level[level][i][j] == 13) && map.candy[i][j].GetFrameIndexOfBitmap() == 0)) {
						if (i == top_random(i, j, level)) {
							map.candy[i][j].set_candy_random(i, j, level, map.candy);
							continue;
						}
						if (search_up_can_down(i, j, level) == -1) {
							continue;
						}
						if (search_up_can_down_type(i, j, level) == 1) {
							map.candy[i][j].SetFrameIndexOfBitmap(map.candy[search_up_can_down(i, j, level)][j].GetFrameIndexOfBitmap());
							map_level[level][i][j] = search_up_can_down_type(i, j, level);
							map_level[level][search_up_can_down(i, j, level)][j] = 1;
							map.candy[search_up_can_down(i, j, level)][j].SetFrameIndexOfBitmap(0);
						}
						else if(search_up_can_down_type(i, j, level) == 4){
							map.bomb[i][j].SetFrameIndexOfBitmap(map.bomb[search_up_can_down(i, j, level)][j].GetFrameIndexOfBitmap());
							map_level[level][i][j] = search_up_can_down_type(i, j, level);
							map_level[level][search_up_can_down(i, j, level)][j] = 1;
							map.candy[search_up_can_down(i, j, level)][j].SetFrameIndexOfBitmap(0);
						}
						else if (search_up_can_down_type(i, j, level) == 12 || search_up_can_down_type(i, j, level) == 13) {
							map.candy[i][j].SetFrameIndexOfBitmap(map.candy[search_up_can_down(i, j, level)][j].GetFrameIndexOfBitmap());
							map.candy[search_up_can_down(i, j, level)][j].SetFrameIndexOfBitmap(0);
						}
					}
				}
			}
		}
		/*bool is_can_down(int x, int y, int level) {
			for (int i = x; i <= candy_lattice_bottom(x, y, level); i++) {
				if (is_candy_empty(level, i, y)) {
					return true;
				}
			}
			return false;
		}
		int candy_lattice_bottom(int x, int y, int level) {
			for (int i; i < 10; i++) {
				if (map_level[level][i][y] == 0) {
					return i - 1;
				}
			}
			return 9;
		}*/
		
		int top_random(int row, int col, int level) {
			for (int i = row - 1; i >= 0; i--) {
				if (map_level[level][i][col] == 0) {
					return row + 1;
				}
			}
			return 0;
		}
		void candy_special_and_special(int clickX, int clickY, int changeX, int changeY, int level) {
			if (map.candy[clickX][clickY].GetFrameIndexOfBitmap() > 6 && map.candy[changeX][changeY].GetFrameIndexOfBitmap() > 6) {
				if (map.candy[clickX][clickY].GetFrameIndexOfBitmap() == 25 && map.candy[changeX][changeY].GetFrameIndexOfBitmap() == 25) {
					for (int k = 0; k < 10; k++) {
						for (int k1 = 0; k1 < 10; k1++) {
							if (map_level[level][k][k1] == 0 || map_level[level][k][k1] == 5) {
								continue;
							}
							object_element(k, k1, level);		
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
								if (map_level[level][k][k1] == 0 || map_level[level][k][k1] == 5) {
									continue;
								}
								object_element(k, k1, level);
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
							if (map_level[level][k][k1] == 0 || map_level[level][k][k1] == 5) {
								continue;
							}
							object_element(k, k1, level);
						}
					}
					for (int k = clickY - 1; k <= clickY + 1; k++) {
						if (k < 0 || k > 9) {
							continue;
						}
						for (int k1 = 0; k1 < 10; k1++) {
							if (map_level[level][k1][k] == 0 || map_level[level][k][k1] == 5) {
								continue;
							}
							object_element(k, k1, level);
						}
					}
				}
				else if ((map.candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 != 0 && (map.candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 != 0) {
					for (int k = 0; k < 10; k++) {
						object_element(clickX, k, level);
						object_element(k, clickY, level);
					}
				}
			}
		}

		int color_connet(int x, int y, bool checkRow, int level) {
			int x1 = x;
			int y1 = y;
			if (map_level[level][x][y] == 0 || map.candy[x][y].is_candy_empty(level, x, y, map.candy)) {
				return 0;
			}
			
			int sum = 0;
			if (checkRow) {
				while (1) {
					if (map_level[level][x][y] == 0 || map.candy[x][y].is_candy_empty(level, x, y, map.candy)) {
						break;
					}
					if (!object_have_color(x,y,level) || !object_have_color(x1, y1, level) || !is_object_same_color(x, y, x1, y1, level)) {
						
						break;
					}
					sum++;
					y1++;
					if (y1 == 10) {
						break;
					}
				}
				return sum;
			}
			else {
				x1 = x;
				y1 = y;
				while (1) {
					if (map_level[level][x][y] == 0 || map.candy[x][y].is_candy_empty(level, x, y, map.candy)) {
						break;
					}
					if (!object_have_color(x, y, level) || !object_have_color(x1, y1, level) || !is_object_same_color(x, y, x1, y1, level)) {
						break;
					}
					sum++;
					x1++;
					if (x1 == 10) {
						break;
					}
				}
				return sum;
			}
		}

		void object_check_element(int clickX, int clickY, int changeX, int changeY, int level) {
			if ((map_level[level][clickX][clickY] == 1 || map_level[level][clickX][clickY] == 12 || map_level[level][clickX][clickY] == 13) && (map_level[level][changeX][changeY] == 1 || map_level[level][changeX][changeY] == 12 || map_level[level][changeX][changeY] == 13)) {
				candy_special_and_special(clickX, clickY, changeX, changeY, level);
			}
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 0 || map_level[level][i][j] == 3 || (5 <= map_level[level][i][j] && map_level[level][i][j] <= 11) || map.candy[i][j].is_candy_empty(level, i, j, map.candy)) {
						continue;
					}
					
					int sum_row = color_connet(i, j, true, level);
					
					candy_need_upgrade(clickX, clickY, changeX, changeY, i, j, sum_row, true, level);
					int sum_col = color_connet(i, j, false, level);
					candy_need_upgrade(clickX, clickY, changeX, changeY, i, j, sum_col, false, level);
				}
			}
		}
		bool object_have_color(int x, int y, int level) {
			if ((map_level[level][x][y] == 1 || map_level[level][x][y] == 2 || map_level[level][x][y] == 4 || map_level[level][x][y] == 12 || map_level[level][x][y] == 13) && (map_level[level][x][y]==1 && map.candy[x][y].GetFrameIndexOfBitmap() != 0 && map.candy[x][y].GetFrameIndexOfBitmap() != 25)) {
				
				return true;
			}
			else {
				return false;
			}
		}
		void map_level_text(int level) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 10, "微軟正黑體", RGB(255, 255, 255));
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					CTextDraw::Print(pDC, 100 + 15 * j, 15 * i, to_string(map_level[level][i][j]));
					CTextDraw::Print(pDC, 270 + 15 * j, 15 * i, to_string(map.candy[i][j].GetFrameIndexOfBitmap()));
				}
			}	
			CTextDraw::Print(pDC, 450 , 15 , to_string(test));
			CDDraw::ReleaseBackCDC();
		}
		void candy_num_text(int level) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 10, "微軟正黑體", RGB(255, 255, 255));
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					CTextDraw::Print(pDC, 400 + 20 * j, 15 * i, to_string(map.candy[i][j].GetFrameIndexOfBitmap()));
				}
			}
			
		}
		bool is_object_same_color(int i, int j, int x, int y, int level) {
			if (!object_have_color(i, j, level) || !object_have_color(x, y, level)) {
				return false;
			}
			
			int color_num = 0;
			int color_num2 = 0;
			if (map.candy[i][j].GetFrameIndexOfBitmap() == 25 || map.candy[x][y].GetFrameIndexOfBitmap() == 25 || map.candy[i][j].GetFrameIndexOfBitmap() == 0 || map.candy[x][y].GetFrameIndexOfBitmap() == 0 || (map_level[level][i][j]==4 && map.bomb[i][j].GetFrameIndexOfBitmap() == 0) || (map_level[level][i][j] == 4 && map.bomb[x][y].GetFrameIndexOfBitmap() == 0)) {
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
				if (map_level[level][i][j] == 4) {
					color_num = map.bomb[i][j].GetFrameIndexOfBitmap();
				}
				else {
					color_num = map.candy[i][j].GetFrameIndexOfBitmap();
				}
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
				if (map_level[level][x][y] == 4) {
					color_num2 = map.bomb[x][y].GetFrameIndexOfBitmap();
				}
				else {
					color_num2 = map.candy[x][y].GetFrameIndexOfBitmap();
				}
			}
			return color_num == color_num2;
		}

		/*template <typename T>
		void object_change( T click_object, int i, int j,T change_object, int x, int y, int level) {
			if (map.candy[x][y].is_candy_empty(level, x, y, map.candy)) {
				return;
			}
			if (map_level[level][i][j] == 0 || map_level[level][i][j] == 2 || (5 <= map_level[level][i][j] && map_level[level][i][j] <= 11) || map_level[level][x][y] == 0 || map_level[level][x][y] == 2 || (5 <= map_level[level][x][y] && map_level[level][x][y] <= 11)) {
				return;
			}
			int have_color[] = { 1, 4, 12, 13 };
			bool out = false;
			if (!out) {
				for (int k = 0; k < 4; k++) {
					if (out) {
						break;
					}
					for (int k1 = k; k1 < 4; k1++) {
						if (map_level[level][i][j] == have_color[k]  && map_level[level][x][y] == have_color[k1]) {
							int num = click_object[i][j].GetFrameIndexOfBitmap();
							click_object[i][j].SetFrameIndexOfBitmap(change_object[x][y].GetFrameIndexOfBitmap());
							change_object[x][y].SetFrameIndexOfBitmap(num);
							out = true;
							break;
						}
					}
				}
			}
			else if (!out) {
				for (int k = 0; k < 4; k++) {
					if (out) {
						break;
					}
					if (map_level[level][i][j] == 3 && map_level[level][x][y] == have_color[k]) {
						click_object[i][j].SetFrameIndexOfBitmap(change_object[x][y].GetFrameIndexOfBitmap());
						out = true;
					}
					else if (map_level[level][i][j] == have_color[k] && map_level[level][x][y] == 3) {
						change_object[x][y].SetFrameIndexOfBitmap(click_object[i][j].GetFrameIndexOfBitmap());
						out = true;
					}
				}
			}
			map.set_candy_lattice_center(i, j, click_object);
			map.set_candy_lattice_center(x, y, change_object);
			if ((map_level[level][i][j] == 1 || map_level[level][i][j] == 12 || map_level[level][i][j] == 13) && (map_level[level][x][y] == 1 || map_level[level][x][y] == 12 || map_level[level][x][y] == 13)) {

			}
			else {
				int num = map_level[level][i][j];
				map_level[level][i][j] = map_level[level][x][y];
				map_level[level][x][y] = num;
			}
		}*/
		void object_change(int i, int j, int x, int y, int level) {
			if (map_level[level][i][j] == 0 || map_level[level][i][j] == 2 || (5 <= map_level[level][i][j] && map_level[level][i][j] <= 11) || map_level[level][x][y] == 0 || map_level[level][x][y] == 2 || (5 <= map_level[level][x][y] && map_level[level][x][y] <= 11)) {
				return;
			}
			if ((map_level[level][i][j] == 1 || map_level[level][i][j] == 12 || map_level[level][i][j] == 13) && (map_level[level][x][y] == 1 || map_level[level][x][y] == 12 || map_level[level][x][y] == 13)) {
				int tem = map.candy[i][j].GetFrameIndexOfBitmap();
				map.candy[i][j].SetFrameIndexOfBitmap(map.candy[x][y].GetFrameIndexOfBitmap());
				map.candy[x][y].SetFrameIndexOfBitmap(tem);
			}
			else if (map_level[level][i][j] == 1 && map_level[level][x][y] == 3) {
				map.candy[x][y].SetFrameIndexOfBitmap(map.candy[i][j].GetFrameIndexOfBitmap());
				map_level[level][i][j] = 3;
				map_level[level][x][y] = 1;
			}
			else if (map_level[level][i][j] == 3 && map_level[level][x][y] == 1) {
				map.candy[i][j].SetFrameIndexOfBitmap(map.candy[x][y].GetFrameIndexOfBitmap());
				map_level[level][i][j] = 1;
				map_level[level][x][y] = 3;
			}
			else if (map_level[level][i][j] == 1 && map_level[level][x][y] == 4) {
				map.candy[x][y].SetFrameIndexOfBitmap(map.candy[i][j].GetFrameIndexOfBitmap());
				map.bomb[i][j].SetFrameIndexOfBitmap(map.bomb[x][y].GetFrameIndexOfBitmap());
				map_level[level][i][j] = 4;
				map_level[level][x][y] = 1;
			}
			else if (map_level[level][i][j] == 4 && map_level[level][x][y] == 1) {
				map.candy[i][j].SetFrameIndexOfBitmap(map.candy[x][y].GetFrameIndexOfBitmap());
				map.bomb[x][y].SetFrameIndexOfBitmap(map.bomb[i][j].GetFrameIndexOfBitmap());
				map_level[level][i][j] = 4;
				map_level[level][x][y] = 1;
			}
			else if (map_level[level][i][j] == 3 && map_level[level][x][y] == 4) {
				map.bomb[i][j].SetFrameIndexOfBitmap(map.bomb[x][y].GetFrameIndexOfBitmap());
				map_level[level][i][j] = 4;
				map_level[level][x][y] = 3;
			}
			else if (map_level[level][i][j] == 4 && map_level[level][x][y] == 3) {
				map.bomb[x][y].SetFrameIndexOfBitmap(map.bomb[i][j].GetFrameIndexOfBitmap());
				map_level[level][i][j] = 4;
				map_level[level][x][y] = 3;
			}
		}
		
		void candy_need_upgrade(int clickX, int clickY, int changeX, int changeY, int i, int j, int sum, bool isRow, int level) {
			if (isRow) {
				
				if (sum == 5) {
					for (int k = j; k < j + sum; k++) {
						if (k == j + 2) {
							if (color_connet(i, k, false, level) >= 3) {
								for (int k1 = i + 1; k1 < i + color_connet(i, k, false, level); k1++) {
									object_element(k1, k, level);
								}
							}
							map.candy[i][k].SetFrameIndexOfBitmap(25);
						}
						else {
							object_element(i, k, level);
						}
						obstacel_destory(i, k, level);
					}
				}
				else if (sum == 4) {
					for (int k = j; k < j + sum; k++) {
						bool hasCandyPack = false;
						if (color_connet(i, k, false, level) >= 3) {
							hasCandyPack = true;
							for (int k1 = i + 1; k1 < i + color_connet(i, k, false, level); k1++) {
								object_element(k1, k, level);
								obstacel_destory(k1, k, level);
							}
							map.candy[i][k].SetFrameIndexOfBitmap(9 + (map.candy[i][k].GetFrameIndexOfBitmap() - 1) * 3);
							obstacel_destory(i, k, level);
						}
						if (k == j + sum - 1 && !hasCandyPack) {
							map.candy[i][clickY].SetFrameIndexOfBitmap(8 + (map.candy[i][k].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						object_element(i, k, level);
						obstacel_destory(i, k, level);
					}
				}
				else if (sum == 3) {
					
					for (int k = j; k < j + sum; k++) {
						if (color_connet(i, k, false, level) >= 3) {
							map.candy[i][k].SetFrameIndexOfBitmap(9 + (map.candy[i][k].GetFrameIndexOfBitmap() - 1) * 3);
							for (int k1 = i + 1; k1 < i + color_connet(i, k, false, level) + 2; k1++) {
								int a = 1;
								object_element(k1, k, level);
								obstacel_destory(k1, k, level);
							}
						}
						else {
							
							object_element(i, k, level);
							obstacel_destory(i, k, level);
						}
					}
				}
			}
			else if (!isRow) {
				if (sum == 5) {
					for (int k = i; k < i + sum; k++) {
						if (k == i + 2) {
							if (color_connet(k, j, true, level) >= 3) {
								for (int k1 = j + 1; k1 < j + color_connet(k, j, true, level); k1++) {
									object_element(k, k1, level);
								}
							}
							map.candy[k][j].SetFrameIndexOfBitmap(25);
						}
						else {
							object_element(k, j, level);
						}
						obstacel_destory(k, j, level);
					}
				}
				else if (sum == 4) {
					for (int k = i; k < i + sum; k++) {
						bool hasCandyPack = false;
						if (color_connet(k, j, true, level) >= 3) {
							hasCandyPack = true;
							for (int k1 = j + 1; k1 < j + color_connet(k, j, true, level); k1++) {
								object_element(k, k1, level);
								obstacel_destory(k, k1, level);
							}
							map.candy[k][j].SetFrameIndexOfBitmap(9 + (map.candy[k][j].GetFrameIndexOfBitmap() - 1) * 3);
						}
						if (k == i + sum - 1 && !hasCandyPack) {
							map.candy[k][j].SetFrameIndexOfBitmap(8 + (map.candy[k][j].GetFrameIndexOfBitmap() - 1) * 3);
							continue;
						}
						object_element(k, j, level);
						obstacel_destory(k, j, level);
					}
				}
				else if (sum == 3) {
					for (int k = i; k < i + sum; k++) {
						if (color_connet(k, j, true, level) >= 3) {
							for (int k1 = j + 1; j < j + color_connet(k, j, true, level); k1++) {
								object_element(k, k1, level);
								obstacel_destory(k, j, level);
							}
							map.candy[k][j].SetFrameIndexOfBitmap(9 + (map.candy[k][j].GetFrameIndexOfBitmap() - 1) * 3);
							obstacel_destory(k, j, level);
							continue;
						}
						object_element(k, j, level);
						obstacel_destory(k, j, level);
					}
				}
			}
		}
		void object_element(int x, int y, int level) {
			if (map_level[level][x][y] == 0 || map_level[level][x][y] == 3 || map_level[level][x][y] == 5) {
				return;
			}
			else if (map_level[level][x][y]==1) {
				
				if (map.candy[x][y].GetFrameIndexOfBitmap() < 7) {
					map.candy[x][y].SetFrameIndexOfBitmap(0);
				}
				else if (map.candy[x][y].GetFrameIndexOfBitmap() == 25) {
					color_ball(level);
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
						object_down(level);
						if (x < 9) {
							x = x + 1;
						}
					}
					map.candy[x][y].SetFrameIndexOfBitmap(0);
				}
			}
			else if (map_level[level][x][y] == 2) {
				map.x_block[x][y].x_block_element(x, y, level);
			}
			else if (map_level[level][x][y] == 4) {
				map.candy[x][y].SetFrameIndexOfBitmap(0);
				map_level[level][x][y] = 1;
			}
			else if (map_level[level][x][y] == 6) {
				map.candy[x][y].SetFrameIndexOfBitmap(0);
				map_level[level][x][y] = 1;
			}
			else if (map_level[level][x][y] == 7) {
				map.candy[x][y].SetFrameIndexOfBitmap(0);
				map_level[level][x][y] = 1;
			}
			else if (map_level[level][x][y] == 8) {
				map_level[level][x][y] = 7;
			}
			else if (map_level[level][x][y] == 9) {
				map_level[level][x][y] = 8;
			}
			else if (map_level[level][x][y] == 10) {
				map_level[level][x][y] = 9;
			}
			else if (map_level[level][x][y] == 11) {
				map_level[level][x][y] =10;
			}
			else if (map_level[level][x][y] == 12) {
				map_level[level][x][y] = 1;
				map.candy[x][y].SetFrameIndexOfBitmap(0);
			}
			else if (map_level[level][x][y] == 13) {
				map_level[level][x][y] = 12;
				map.candy[x][y].SetFrameIndexOfBitmap(0);
			}	
		}
		void chocolate_generate(int level) {
			for (int t = 0; t < rand() % 3 + 1; t++) {
				bool have_generated = false;
				while (!have_generated) {
					int rand_x = rand() % 10;
					int rand_y = rand() % 10;
					if (map_level[level][rand_x][rand_y] == 5 || map_level[level][rand_x][rand_y] == 6) {
						int generate_direction = rand() % 4;
						int generate_direction_init = generate_direction;
						while (!have_generated) {
							
							if (generate_direction == 0) {
								if (0 <= rand_x - 1 && rand_x - 1 <= 10) {
									if (map_level[level][rand_x - 1][rand_y] == 1) {
										map_level[level][rand_x - 1][rand_y] = 6;
										have_generated = true;
										break;
									}								
								}
							}
							else if (generate_direction == 1) {
								if (0 <= rand_y + 1 && rand_y + 1 <= 10) {
									if (map_level[level][rand_x][rand_y+1] == 1) {
										map_level[level][rand_x][rand_y+1] = 6;
										have_generated = true;
										break;
									}
								}
							}
							else if (generate_direction == 2) {
								if (0 <= rand_x + 1 && rand_x + 1 <= 10) {
									if (map_level[level][rand_x + 1][rand_y] == 1) {
										map_level[level][rand_x + 1][rand_y] = 6;
										have_generated = true;
										break;
									}
								}
							}
							else if (generate_direction == 3) {
								if (0 <= rand_y-1 && rand_y - 1 <= 10) {
									if (map_level[level][rand_x ][rand_y - 1] == 1) {
										map_level[level][rand_x][rand_y - 1] = 6;
										have_generated = true;
										break;
									}
								}
							}
							if (!have_generated) {
								generate_direction++;
							}
							if (generate_direction_init == generate_direction) {
								break;
							}
						}
					}			
				}
			}
		}
		void obstacel_destory(int x,int y,int level) {
			if (0 <= x - 1 && x - 1 < 10) {
				if (map_level[level][x - 1][y] == 6) {
					map_level[level][x - 1][y] = 1;
					map.candy[x - 1][y].SetFrameIndexOfBitmap(0);
					step_has_chocolate_destory = true;
				}
				else if (7<=map_level[level][x - 1][y]&& map_level[level][x - 1][y] <=11) {
					if ( map_level[level][x - 1][y]==7) {
						map_level[level][x - 1][y] = 1;
						map.candy[x - 1][y].SetFrameIndexOfBitmap(0);
					}
					else {
						map_level[level][x - 1][y]--;
					}
				}
			}
			else if (0 <= y + 1 && y + 1 < 10) {
				if (map_level[level][x][y + 1] == 6) {
					map_level[level][x][y + 1] = 1;
					map.candy[x][y + 1].SetFrameIndexOfBitmap(0);
					step_has_chocolate_destory = true;
				}
				else if (7 <= map_level[level][x][y+1] && map_level[level][x][y + 1] <= 11) {
					if (map_level[level][x][y + 1] == 7) {
						map_level[level][x][y + 1] = 1;
						//map.candy[level][x][y + 1].SetFrameIndexOfBitmap(0);
					}
					else {
						map_level[level][x][y + 1]--;
					}
				}
			}
			else if (0 <= x + 1 && x + 1 < 10) {
				if (map_level[level][x + 1][y] == 6) {
					map_level[level][x + 1][y] = 1;
					map.candy[x + 1][y].SetFrameIndexOfBitmap(0);
					step_has_chocolate_destory = true;
				}
				else if (7 <= map_level[level][x + 1][y] && map_level[level][x + 1][y] <= 11) {
					if (map_level[level][x + 1][y] == 7) {
						map_level[level][x + 1][y] = 1;
						map.candy[x + 1][y].SetFrameIndexOfBitmap(0);
					}
					else {
						map_level[level][x + 1][y]--;
					}
				}
			}
			else if (0 <= y - 1 && y - 1 < 10) {
				if (map_level[level][x][y - 1] == 6) {
					map_level[level][x][y - 1] = 1;
					map.candy[x][y + 1].SetFrameIndexOfBitmap(0);
					step_has_chocolate_destory = true;
				}
				else if (7 <= map_level[level][x][y - 1] && map_level[level][x][y - 1] <= 11) {
					if (map_level[level][x][y - 1] == 7) {
						map_level[level][x][y - 1] = 1;
						map.candy[x][y - 1].SetFrameIndexOfBitmap(0);	
					}
					else {
						map_level[level][x][y - 1]--;
					}
				}
			}
		}
		void color_ball(int level) {
			if (map.candy[clickX][clickX].GetFrameIndexOfBitmap() == 25) {
				for (int k = 0; k < 10; k++) {
					for (int z = 0; z < 10; z++) {
						if (map_level[level][k][z] == 0 || map_level[level][k][z] == 3 || map_level[level][k][z] == 5) {
							continue;
						}
						if (k == clickX && z == clickY) {
							continue;
						}
						if (map.candy[k][z].GetFrameIndexOfBitmap() == map.candy[changeX][changeY].GetFrameIndexOfBitmap()) {
							object_element(k, z, level);
						}
					}
				}
				map.candy[clickX][clickY].SetFrameIndexOfBitmap(0);
			}
			else if (map.candy[changeX][changeY].GetFrameIndexOfBitmap() == 25) {
				for (int k = 0; k < 10; k++) {
					for (int z = 0; z < 10; z++) {
						if (map_level[level][k][z] == 0) {
							continue;
						}
						if (k == changeX && z == changeY) {
							continue;
						}
						if (map.candy[k][z].GetFrameIndexOfBitmap() == map.candy[clickX][clickX].GetFrameIndexOfBitmap()) {
							object_element(k, z, level);
						}
					}
				}
				map.candy[changeX][changeY].SetFrameIndexOfBitmap(0);
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
		bool step_has_chocolate_destory = false;
		CSpecialEffect time;
		int test = 0;
	};
}


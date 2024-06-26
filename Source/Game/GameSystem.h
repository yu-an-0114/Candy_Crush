﻿//#ifdef MAP_H
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
#include "Effect.h"
#include "Score.h"
#include "Step.h"
#include "Goal.h"
using namespace std;

namespace game_framework {
	class GameSystem {
	public:
		int get_object_type(int x, int y, int level) {
			return map_level[level][x][y];
		}
		void set_object_type(int x, int y, int level, int type) {
			map_level[level][x][y] = type;
		}

		int search_up_can_down_row(int x, int col, int level) {
			for (int i = x - 1; i >= map.map_top(x, col, level); i--) {
				if (map.is_empty(i, col, level, map.candy)) {
					continue;
				}
				if (map.Candy.is_candy(i, col, level, map.candy) || map.Cherry.is_cherry(i, col, level) || map.Bomb.is_bomb(i, col, level) || map.Glass.is_glass(i, col, level)) {
					return i;
				}
				if (map.X_Block.is_x_block(i, col, level) || map.Sugar.is_sugar(i, col, level)) {
					return -1;
				}
			}
			return -1;
		}

		void object_down(int level) {
			for (int j = 0; j < 10; j++) {
				for (int i = 9; i >= 0; i--) {
					if (map.is_empty(i, j, level, map.candy)) {
						if (i == map.map_top(i, j, level)) {
							map.candy[i][j].set_candy_random(i, j, map.candy);
							continue;
						}
						if (search_up_can_down_row(i, j, level) == -1) {
							continue;
						}
						if (map.Candy.is_candy(search_up_can_down_row(i, j, level), j, level, map.candy)) {
							map.candy[i][j].SetFrameIndexOfBitmap(map.candy[search_up_can_down_row(i, j, level)][j].GetFrameIndexOfBitmap());
							set_object_type(i, j, level, 1);
							set_object_type(search_up_can_down_row(i, j, level), j, level, 1);
							map.candy[search_up_can_down_row(i, j, level)][j].SetFrameIndexOfBitmap(0);
						}
						else if (map.Cherry.is_cherry(search_up_can_down_row(i, j, level), j, level)) {
							set_object_type(i, j, level, 3);
							set_object_type(search_up_can_down_row(i, j, level), j, level, 1);
							map.candy[search_up_can_down_row(i, j, level)][j].SetFrameIndexOfBitmap(0);
						}
						else if (map.Bomb.is_bomb(search_up_can_down_row(i, j, level), j, level)) {
							int tem2 = map.Bomb.get_bomb_step(search_up_can_down_row(i, j, level), j, map.bomb);
							map.bomb[i][j].SetFrameIndexOfBitmap(map.bomb[search_up_can_down_row(i, j, level)][j].GetFrameIndexOfBitmap());
							set_object_type(i, j, level, 4);
							set_object_type(search_up_can_down_row(i, j, level), j, level, 1);
							map.candy[search_up_can_down_row(i, j, level)][j].SetFrameIndexOfBitmap(0);
							int tem = map.Bomb.get_bomb_step(i, j, map.bomb);
							
							map.Bomb.set_bomb_step(i, j, map.bomb,tem2);
							map.Bomb.set_bomb_step(search_up_can_down_row(i, j, level), j, map.bomb, tem);
						}
						else if (map.Glass.is_glass(search_up_can_down_row(i, j, level), j, level)) {
							map.candy[i][j].SetFrameIndexOfBitmap(map.candy[search_up_can_down_row(i, j, level)][j].GetFrameIndexOfBitmap());
							map.candy[search_up_can_down_row(i, j, level)][j].SetFrameIndexOfBitmap(0);
						}
					}
				}
			}
		}
		
		bool is_can_down(int x, int col, int level) {
			for (int i = x + 1; i <= map.map_bottom(x, col, level); i++) {
				if (map.is_empty(i, col, level, map.candy)) {
					return true;
				}
			}
			return false;
		}
		int can_down_row(int x, int col, int level) {
			for (int i = x + 1; i <= map.map_bottom(x, col, level); i++) {
				if (map.is_empty(i, col, level, map.candy)) {
					return i;
				}
			}
			return -1;
		}
		
		void candy_special_and_special(int clickX, int clickY, int changeX, int changeY, int level) {
			if (Ui.debug_mode) {
				return;
			}
			if (map.candy[clickX][clickY].GetFrameIndexOfBitmap() > 6 && map.candy[changeX][changeY].GetFrameIndexOfBitmap() > 6) {
				color_ball(level);
				if ((map.candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 == 0 && (map.candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 == 0) {
					for (int t = 0; t < 2; t++) {
						for (int k = clickX - 2; k <= clickX + 2; k++) {
							for (int k1 = clickY - 2; k1 <= clickY + 2; k1++) {
								if (k < 0 || k > 9 || k1 < 0 || k1 > 9 || (k== clickX && k1 == clickY) || (k == changeX && k1 == changeY)) {
									continue;
								}
								if (map.none_map(k, k1, level) || map.Chocolate_Machine.is_chocolate_machine(k, k1, level) || map.Cherry.is_cherry(k, k1, level)) {
									continue;
								}
								object_element(k, k1, level, 0);
							}
						}
						if (t == 1) {
							map.candy[clickX][clickY].SetFrameIndexOfBitmap(0);
							map.candy[changeX][changeY].SetFrameIndexOfBitmap(0);
							continue;
						}
						clickX = clickX + 2;
						changeX = changeX + 2;
					}				
				}
				else if (((map.candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 == 0 && (map.candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 != 0) || ((map.candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 != 0 && (map.candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 == 0)) {
					for (int k = clickX - 1; k <= clickX + 1; k++) {
						for (int k1 = 0; k1 < 10; k1++) {
							if (k < 0 || k > 9 || k1 < 0 || k1 > 9 || (k == clickX && k1 == clickY) || (k == changeX && k1 == changeY)) {
								continue;
							}
							if (map.none_map(k, k1, level) || map.Chocolate_Machine.is_chocolate_machine(k, k1, level) || map.Cherry.is_cherry(k, k1, level)) {
								continue;
							}
							object_element(k, k1, level, 0);
						}
					}
					for (int k = clickY - 1; k <= clickY + 1; k++) {
						for (int k1 = 0; k1 < 10; k1++) {
							if (k < 0 || k > 9 || k1 < 0 || k1 > 9 || (k1 == clickX && k == clickY) || (k1 == changeX && k == changeY)) {
								continue;
							}
							if (map.none_map(k1, k, level) || map.Chocolate_Machine.is_chocolate_machine(k1, k, level) || map.Cherry.is_cherry(k1, k, level)) {
								continue;
							}
							object_element(k1, k, level,0);
						}
					}
					map.candy[clickX][clickY].SetFrameIndexOfBitmap(0);
					map.candy[changeX][changeY].SetFrameIndexOfBitmap(0);
				}
				else if ((map.candy[clickX][clickY].GetFrameIndexOfBitmap() - 6) % 3 != 0 && (map.candy[changeX][changeY].GetFrameIndexOfBitmap() - 6) % 3 != 0) {
					for (int k = 0; k < 10; k++) {
						object_element(clickX, k, level, 0);
						object_element(k, clickY, level, 0);
					}
				}
			}
		}
		
		int color_connet(int x, int y, bool checkRow, int level, bool check_positive) {
			int x1 = x;
			int y1 = y;
			int sum = 0;
			if (checkRow) {
				if (check_positive) {
					while (1) {
						if (map.none_map(x1, y1, level) || map.is_empty(x1, y1, level, map.candy)) {
							break;
						}
						if (!object_have_color(x, y, level) || !object_have_color(x1, y1, level) || !is_object_same_color(x, y, x1, y1, level)) {
							break;
						}
						sum++;
						y1++;
						if (y1 == 10) {
							break;
						}
					}
				}
				else {
					while (1) {
						if (map.none_map(x1, y1, level) || map.is_empty(x1, y1, level, map.candy)) {
							break;
						}
						if (!object_have_color(x, y, level) || !object_have_color(x1, y1, level) || !is_object_same_color(x, y, x1, y1, level)) {
							break;
						}
						sum++;
						y1--;
						if (y1 < 0) {
							break;
						}
					}
				}
			}
			else {
				if (check_positive) {
					while (1) {
						if (map.none_map(x1, y1, level) || map.is_empty(x1, y1, level, map.candy)) {
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
				}
				else {
					while (1) {
						if (map.none_map(x1, y1, level) || map.is_empty(x1, y1, level, map.candy)) {
							break;
						}
						if (!object_have_color(x, y, level) || !object_have_color(x1, y1, level) || !is_object_same_color(x, y, x1, y1, level)) {
							break;
						}
						sum++;
						x1--;
						if (x1 < 0) {
							break;
						}
					}
				}
			}
			return sum;
		}

		void object_check_element(int clickX, int clickY, int changeX, int changeY, int level) {
			
			if ((map_level[level][clickX][clickY] == 1 || map_level[level][clickX][clickY] == 12 || map_level[level][clickX][clickY] == 13) && (map_level[level][changeX][changeY] == 1 || map_level[level][changeX][changeY] == 12 || map_level[level][changeX][changeY] == 13)) {
				candy_special_and_special(clickX, clickY, changeX, changeY, level);
			}
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 0 || map_level[level][i][j] == 3 || (5 <= map_level[level][i][j] && map_level[level][i][j] <= 11) || map.is_empty( i, j,level, map.candy)) {

						continue;
					}
					int sum_row = color_connet(i, j, true, level, true);
					
					if (sum_row >= 3) {

						candy_need_upgrade(clickX, clickY, changeX, changeY, i, j, sum_row, true, level);
					}
					int sum_col = color_connet(i, j, false, level, true);
			
					if (sum_col >= 3) {
						
						candy_need_upgrade(clickX, clickY, changeX, changeY, i, j, sum_col, false, level);
					}
				}
			}
		}

		bool object_have_color(int x, int y, int level) {

			if ((map_level[level][x][y] == 2 || map_level[level][x][y] == 4 || map_level[level][x][y] == 12 || map_level[level][x][y] == 13) || (map_level[level][x][y]==1 && (map.candy[x][y].GetFrameIndexOfBitmap() != 0 && map.candy[x][y].GetFrameIndexOfBitmap() != 25))) {	
				
				return true;
			}
			else {
				
				return false;
			}
		}
		void map_level_text(int level) {
			CDC *pDC = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(pDC, 10, "Futura", RGB(255, 255, 255));
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					CTextDraw::Print(pDC, 100 + 15 * j, 15 * i, to_string(map_level[level][i][j]));
					CTextDraw::Print(pDC, 520 + 20 * j, 15 * i, to_string(map.candy[i][j].GetFrameIndexOfBitmap()));
		
				}
			}	

			CDDraw::ReleaseBackCDC();
		}

		bool is_object_same_color(int i, int j, int x, int y, int level) {
			if (!object_have_color(i, j, level) || !object_have_color(x, y, level)) {
				return false;
			}
			int color_num = 0;
			int color_num2 = 0;
			if ((map_level[level][i][j] == 1 && (map.candy[i][j].GetFrameIndexOfBitmap() == 25 || map.candy[i][j].GetFrameIndexOfBitmap() == 0)) || (map_level[level][x][y] == 1 && (map.candy[x][y].GetFrameIndexOfBitmap() == 25 || map.candy[x][y].GetFrameIndexOfBitmap() == 0)) || (map_level[level][i][j] == 4 && map.bomb[i][j].GetFrameIndexOfBitmap() == 0) || (map_level[level][x][y] == 4 && map.bomb[x][y].GetFrameIndexOfBitmap() == 0)) {
				return false;
			}
			if (map_level[level][i][j] == 1 || map_level[level][i][j] == 2 || map_level[level][i][j] == 12 || map_level[level][i][j] == 13) {
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
			}
			else if(map_level[level][i][j] == 4){
				color_num = map.bomb[i][j].GetFrameIndexOfBitmap();		
			}
			if (map_level[level][x][y] == 1 || map_level[level][x][y] == 2 || map_level[level][x][y] == 12 || map_level[level][x][y] == 13) {
				if (map.candy[x][y].GetFrameIndexOfBitmap() > 6) {
					if (map.candy[x][y].GetFrameIndexOfBitmap() % 3 == 0) {
						color_num2 = (int)ceil((map.candy[x][y].GetFrameIndexOfBitmap() - 6) / 3);
					}
					else {
						color_num2 = (int)ceil((map.candy[x][y].GetFrameIndexOfBitmap() - 6) / 3) + 1;
					}
				}
				else {
					color_num2= map.candy[x][y].GetFrameIndexOfBitmap();
				}
			}
			else if (map_level[level][x][y] == 4) {
				color_num2 = map.bomb[x][y].GetFrameIndexOfBitmap();
			}

			return color_num == color_num2;
		}

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
				map.candy[i][j].SetFrameIndexOfBitmap(0);
				effectlevel.shine(i, j);
				map_level[level][i][j] = 3;
				map_level[level][x][y] = 1;
			}
			else if (map_level[level][i][j] == 3 && map_level[level][x][y] == 1) {
				map.candy[i][j].SetFrameIndexOfBitmap(map.candy[x][y].GetFrameIndexOfBitmap());
				map.candy[x][y].SetFrameIndexOfBitmap(0);
				effectlevel.shine(x, y);
				map_level[level][i][j] = 1;
				map_level[level][x][y] = 3;
			}
			else if (map_level[level][i][j] == 1 && map_level[level][x][y] == 4) {
				map.candy[x][y].SetFrameIndexOfBitmap(map.candy[i][j].GetFrameIndexOfBitmap());
				map.bomb[i][j].SetFrameIndexOfBitmap(map.bomb[x][y].GetFrameIndexOfBitmap());
				map.candy[i][j].SetFrameIndexOfBitmap(0);
				effectlevel.shine(i, j);
				map_level[level][i][j] = 4;
				map_level[level][x][y] = 1;
			
				int tem = map.Bomb.get_bomb_step(i, j, map.bomb);
				map.Bomb.set_bomb_step(i, j, map.bomb, map.Bomb.get_bomb_step(x, y, map.bomb));
				map.Bomb.set_bomb_step(x, y, map.bomb, tem);
			}
			else if (map_level[level][i][j] == 4 && map_level[level][x][y] == 1) {
				map.candy[i][j].SetFrameIndexOfBitmap(map.candy[x][y].GetFrameIndexOfBitmap());
				map.bomb[x][y].SetFrameIndexOfBitmap(map.bomb[i][j].GetFrameIndexOfBitmap());
				map.candy[x][y].SetFrameIndexOfBitmap(0);
				effectlevel.shine(x, y);
				map_level[level][i][j] = 1;
				map_level[level][x][y] = 4;
				int tem = map.Bomb.get_bomb_step(i, j, map.bomb);
				map.Bomb.set_bomb_step(i, j, map.bomb, map.Bomb.get_bomb_step(x, y, map.bomb));
				map.Bomb.set_bomb_step(x, y, map.bomb, tem);
			}
			else if (map_level[level][i][j] == 3 && map_level[level][x][y] == 4) {
				map.bomb[i][j].SetFrameIndexOfBitmap(map.bomb[x][y].GetFrameIndexOfBitmap());
				map_level[level][i][j] = 4;
				map_level[level][x][y] = 3;
				int tem = map.Bomb.get_bomb_step(i, j, map.bomb);
				map.Bomb.set_bomb_step(i, j, map.bomb, map.Bomb.get_bomb_step(x, y, map.bomb));
				map.Bomb.set_bomb_step(x, y, map.bomb, tem);
			}
			else if (map_level[level][i][j] == 4 && map_level[level][x][y] == 3) {
				map.bomb[x][y].SetFrameIndexOfBitmap(map.bomb[i][j].GetFrameIndexOfBitmap());
				map_level[level][i][j] = 4;
				map_level[level][x][y] = 3;
				int tem = map.Bomb.get_bomb_step(i, j, map.bomb);
				map.Bomb.set_bomb_step(i, j, map.bomb, map.Bomb.get_bomb_step(x, y, map.bomb));
				map.Bomb.set_bomb_step(x, y, map.bomb, tem);
			}
			else if (map_level[level][i][j] == 4 && map_level[level][x][y] == 4) {
				int tem = map.bomb[i][j].GetFrameIndexOfBitmap();
				int tem2 = map.bomb[x][y].GetFrameIndexOfBitmap();
				map.bomb[i][j].SetFrameIndexOfBitmap(tem2);
				map.bomb[x][y].SetFrameIndexOfBitmap(tem);
				int tem3 = map.Bomb.get_bomb_step(i, j, map.bomb);
				map.Bomb.set_bomb_step(i, j, map.bomb, map.Bomb.get_bomb_step(x, y, map.bomb));
				map.Bomb.set_bomb_step(x, y, map.bomb, tem3);
			}
		}
		int get_candy_color(int i, int j,int level) {
			int color_num = 0;
			if (map_level[level][i][j] == 1 || map_level[level][i][j] == 2 || map_level[level][i][j] == 12 || map_level[level][i][j] == 13) {
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
			}
			
			if (map_level[level][i][j] == 4) {
				color_num = map.bomb[i][j].GetFrameIndexOfBitmap();
			}
			return color_num;
		}
		void candy_need_upgrade(int clickX, int clickY, int changeX, int changeY, int i, int j, int sum, bool isRow, int level) {
			
			
			int color = get_candy_color(i, j,level);
			
			if (isRow) {
				
				if (sum == 5) {
					for (int k = j; k < j + sum; k++) {
						if (k == j + 2) {
							if (color_connet(i, k, false, level,true) >= 3) {
								int tem = color_connet(i, k, false, level, true);
								for (int k1 = i + 1; k1 < i + tem; k1++) {
									object_element(k1, k, level,0);
									obstacel_destory(k1, k, level);
								}
							}
							map.candy[i][k].SetFrameIndexOfBitmap(25);
							obstacel_destory(i, k, level);
						}
						else {
							object_element(i, k, level,0);
							obstacel_destory(i, k, level);
						}
					}
				}
				else if (sum == 4) {
					bool hasCandyPack = false;
					
					for (int k = j; k < j + sum; k++) {
						if (color_connet(i, k, false, level,true) >= 3) {
							hasCandyPack = true;
							int tem = color_connet(i, k, false, level, true);
							for (int k1 = i + 1; k1 < i + tem; k1++) {	
								object_element(k1, k, level,0);
								obstacel_destory(k1, k, level);
							}
							map.candy[i][k].SetFrameIndexOfBitmap(9 + (color - 1) * 3);
							obstacel_destory(i, k, level);
							continue;
						}
						object_element(i, k, level,0);
						obstacel_destory(i, k, level);
						if (k == j + sum - 1 && !hasCandyPack) {
							map.candy[i][clickY].SetFrameIndexOfBitmap(8 + (color - 1) * 3);
							obstacel_destory(i, clickY, level);
						}
					}
				}
				else if (sum == 3) {
					for (int k = j; k < j + sum; k++) {
						if (color_connet(i, k, false, level,true) >= 3) {
							int tem = color_connet(i, k, false, level, true);
							map.candy[i][k].SetFrameIndexOfBitmap(9 + (color - 1) * 3);
							obstacel_destory(i, k, level);
							for (int k1 = i + 1; k1 < i + tem + 2; k1++) {
								int a = 1;
								object_element(k1, k, level,0);
								obstacel_destory(k1, k, level);
							}
						}
						else {	
							object_element(i, k, level,0);
							obstacel_destory(i, k, level);
						}
					}
				}
			}
			else if (!isRow) {
				if (sum == 5) {
					for (int k = i; k < i + sum; k++) {
						if (k == i + 2) {
							if (color_connet(k, j, true, level,true) >= 3) {
								int tem = color_connet(k, j, true, level, true);
								for (int k1 = j + 1; k1 < j + tem; k1++) {
									object_element(k, k1, level,0);
									obstacel_destory(k, k1, level);
								}
							}
							if (color_connet(k, j, true, level, false) >= 3) {
								int tem = color_connet(k, j, true, level, false);
								for (int k1 = j - 1; k1 > j - tem; k1--) {
									object_element(k, k1, level,0);
									obstacel_destory(k, k1, level);
								}
							}
							map.candy[k][j].SetFrameIndexOfBitmap(25);
							obstacel_destory(k, j, level);
						}
						else {
							object_element(k, j, level,0);
							obstacel_destory(k, j, level);
						}
					}
				}
				else if (sum == 4) {
					bool hasCandyPack = false;
					for (int k = i; k < i + sum; k++) {
						if (color_connet(k, j, true, level, true) + color_connet(k, j, true, level, false) - 1 >= 3) {
							hasCandyPack = true;
							int tem = color_connet(k, j, true, level, true);
							for (int k1 = j - color_connet(k, j, true, level, false) + 1; k1 < j + tem; k1++) {
								if (k1 == j) {
									continue;
								}
								object_element(k, k1, level,0);
								obstacel_destory(k, k1, level);
							}
							map.candy[k][j].SetFrameIndexOfBitmap(9 + (color - 1) * 3);
							obstacel_destory(k, j, level);
							continue;
						}
						if (k == i + sum - 1 && !hasCandyPack) {
							map.candy[k][j].SetFrameIndexOfBitmap(7 + (color - 1) * 3);
							obstacel_destory(k, j, level);
							continue;
						}
						object_element(k, j, level,0);
						obstacel_destory(k, j, level);
					}
				}
				else if (sum == 3) {	
					
					for (int k = i; k < i + sum; k++) {
						if (color_connet(k, j, true, level, true) + color_connet(k, j, true, level, false) - 1 >= 3) {
							int tem = color_connet(k, j, true, level, true);
							for (int k1 = j - color_connet(k, j, true, level, false) + 1; k1 < j +tem; k1++) {
								if (k1 == j) {
									continue;
								}
								object_element(k, k1, level,0);
								obstacel_destory(k, k1, level);
							}
							map.candy[k][j].SetFrameIndexOfBitmap(9 + (color - 1) * 3);
							obstacel_destory(k, j, level);
							continue;
						}
						object_element(k, j, level,0);
						obstacel_destory(k, j, level);
					}
				}
			}
		}
		
		void game_init(int level) {
			map.build_map(level);
			Step::step = Step.stepInit(level);

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					pre_map_level[i][j] = get_object_type(i, j, level);
				}
			}
			int init_map_level[10][10];
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					init_map_level[i][j] = get_object_type(i, j, level);
				}
			}
			map.build_map(level);
			for (int t = 0; t < 3; t++) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						while(color_connet(i, j, true, level, true) >= 3 || color_connet(i, j, false, level, true) >= 3 || color_connet(i, j, true, level, false) >= 3 || color_connet(i, j, false, level, false) >= 3) {
							if (get_object_type(i, j, level) == 1) {
								map.candy[i][j].set_candy_random(i, j, map.candy);
							}
							else if (get_object_type(i, j, level) == 2) {
								map.candy[i][j].set_candy_random(i, j, map.candy);
							}
							else if (get_object_type(i, j, level) == 4) {
								map.Bomb.set_bomb_random(i, j, level,map.bomb);
							}
							
							else if (map.Glass.is_glass(i,j,level)) {
								map.candy[i][j].set_candy_random(i, j, map.candy);
							}
						}	
					}
				}
			}
			map.Bomb.bomb_init(level, map.bomb);
			Goal.GoalSetting(level);
			Score::score = 0;
		}

		void object_element(int x, int y, int level,int t) {
			if (t == 0) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						visited[i][j] = 0;
					}
				}
			}
			if ((map_level[level][x][y]==1 || map_level[level][x][y] == 2 || map_level[level][x][y] == 12 || map_level[level][x][y] == 13)&& map.candy[x][y].GetFrameIndexOfBitmap() > 0) {
				Goal.SetGoal(map.candy[x][y].GetFrameIndexOfBitmap());
			}
			if (map_level[level][x][y] == 2) {
				Goal.SetGoal(29);
			}
			if (map_level[level][x][y] == 3) {
				Goal.SetGoal(26);
			}
			
			if (map_level[level][x][y] == 4) {
				Goal.SetGoal(30);
			}
			
			if (map_level[level][x][y] == 7) {
				Goal.SetGoal(28);
			}
			if (map_level[level][x][y] == 12) {
				Goal.SetGoal(27);
			}
			Score::score += 100;
			t++;
			if (map_level[level][x][y] == 0 || map_level[level][x][y] == 3 || map_level[level][x][y] == 5 || visited[x][y] == 1) {
				return;
			}
			visited[x][y] = 1;
			if (map_level[level][x][y] == 1) {
				int frameIndex = map.candy[x][y].GetFrameIndexOfBitmap();
				if (frameIndex < 7) {
					map.candy[x][y].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x, y);
				}
				else if (frameIndex == 25) {
					map.candy[x][y].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x, y);
					color_ball(level);
				}
				else if (frameIndex % 3 == 1) {
					map.candy[x][y].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x, y);
					for (int i = 0; i < 10; i++) {
						object_element(x, i, level,t);			
					}
				}
				else if (frameIndex % 3 == 2) {
					map.candy[x][y].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x, y);
					for (int i = 0; i < 10; i++) {
						object_element(i, y, level, t);
					}
				}
				else {
					for (int i = 0; i < 2; i++) {
						if (x - 1 >= 0 && y - 1 >= 0 ) {
							object_element(x - 1, y - 1, level, t);
						
						}
						if (x - 1 >= 0) {
							object_element(x - 1, y , level, t);
						}
						if (x - 1 >= 0 && y + 1 < 10) {
							object_element(x - 1, y + 1, level, t);
						}
						if (y - 1 >= 0) {
							object_element(x , y - 1, level, t);
						}
						if (y + 1 < 10 ) {
							object_element(x, y + 1, level, t);
						}
						if (x + 1 < 10 && y - 1 >= 0) {
							object_element(x+1, y - 1, level, t);
						}
						if (x + 1 < 10 ) {
							object_element(x + 1, y , level, t);
						}
						if (x + 1 < 10 && y + 1 < 10) {
							object_element(x + 1, y + 1, level, t);
						}
						object_down(level);
						if (x < 9) {
							x = x + 1;
						}
					}
					map.candy[x][y].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x, y);
				}
			}
			else if (map_level[level][x][y] == 2) {
				map.x_block[x][y].x_block_element(x, y, level);
			}
			else if (map_level[level][x][y] == 4) {
				map.candy[x][y].SetFrameIndexOfBitmap(0);
				effectlevel.shine(x, y);
				map_level[level][x][y] = 1;
			}
			else if (map_level[level][x][y] == 6) {
				map.candy[x][y].SetFrameIndexOfBitmap(0);
				effectlevel.shine(x, y);
				map_level[level][x][y] = 1;
				step_has_chocolate_destory = true;
			}
			else if (7<=map_level[level][x][y] && map_level[level][x][y]<=11) {
				if (map_level[level][x][y] == 7) {
					map.candy[x][y].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x, y);
					map_level[level][x][y] = 1;
				}
				else {
					map_level[level][x][y]--;
					map.sugar[x][y].SetFrameIndexOfBitmap(map.sugar[x][y].GetFrameIndexOfBitmap()-1);
				}
			}
			else if (map_level[level][x][y] == 12) {
				map_level[level][x][y] = 1;
				map.candy[x][y].SetFrameIndexOfBitmap(0);
				effectlevel.shine(x, y);
			}
			else if (map_level[level][x][y] == 13) {
				map_level[level][x][y] = 12;
				map.glass[x][y].SetFrameIndexOfBitmap(0);
				map.candy[x][y].SetFrameIndexOfBitmap(0);
				effectlevel.shine(x, y);
			}
			return;
		}

		bool can_change(int x, int y,int i ,int j, int level) {
			if (map.candy[i][j].GetFrameIndexOfBitmap() == 25 || map.candy[x][y].GetFrameIndexOfBitmap() == 25) {
				return true;
			}
			if (map.candy[i][j].GetFrameIndexOfBitmap()>6 && map.candy[x][y].GetFrameIndexOfBitmap() > 6) {
				return true;
			}
			object_change(x, y, i, j, level);
			int change_row_positive = color_connet(x, y, true, level, true);
			int change_row_unpositive = color_connet(x, y, true, level, false);
			int change_col_positive = color_connet(x, y, false, level, true);
			int change_col_unpositive = color_connet(x, y, false, level, false);

			if (change_row_positive + change_row_unpositive - 1 >= 3 || change_col_positive + change_col_unpositive-1 >= 3) {
				object_change(x, y, i, j, level);
				return true;
			}
			else {
				object_change(x, y, i, j, level);
				return false;
			}	
		}
		void chocolate_generate(int level) {
			bool out = true;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 5 || map_level[level][i][j] == 6) {
						out = false;
					}
				}
			}
			if (out) {
				return;
			}
			int tem = rand() % 3 + 1;
			for (int t = 0; t < tem; t++) {
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
								if (generate_direction == 4) {
									generate_direction = 0;
								}
							}
							if (generate_direction_init == generate_direction) {
								have_generated = true;
								break;
							}
						}
					}			
				}
			}
			
		}
		void obstacel_destory(int x,int y,int level) {
			if (0 <= x - 1 && x - 1 < 10) {
				if (6<=map_level[level][x - 1][y] && map_level[level][x - 1][y]<=7) {
					if (map_level[level][x - 1][y] == 6) {
						step_has_chocolate_destory = true;
					}
					map_level[level][x - 1][y] = 1;
					map.candy[x - 1][y].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x-1, y);
				}
				else if (8 <= map_level[level][x - 1][y] && map_level[level][x - 1][y] <= 11) {
					map_level[level][x - 1][y]--;
					int sugar_index = map.sugar[x - 1][y].GetFrameIndexOfBitmap();
					map.sugar[x - 1][y].SetFrameIndexOfBitmap(sugar_index - 1);
				}
			}
			if (0 <= y + 1 && y + 1 < 10) {
				if (6 <= map_level[level][x][y+1] && map_level[level][x][y + 1] <= 7) {
					if (map_level[level][x][y + 1] == 6) {
						step_has_chocolate_destory = true;
					}
					map_level[level][x][y + 1] = 1;
					map.candy[x][y + 1].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x, y+1);
					
				}
				else if (8 <= map_level[level][x][y + 1] && map_level[level][x][y + 1] <= 11) {
					map_level[level][x][y + 1] --;
					int sugar_index = map.sugar[x][y + 1].GetFrameIndexOfBitmap();
					map.sugar[x][y + 1].SetFrameIndexOfBitmap(sugar_index - 1);
				}
			}
			if (0 <= x + 1 && x + 1 < 10) {
				
				if (6 <= map_level[level][x + 1][y] && map_level[level][x + 1][y] <= 7) {
					if (map_level[level][x + 1][y] == 6) {
						step_has_chocolate_destory = true;

					}
					map_level[level][x + 1][y] = 1;
					map.candy[x + 1][y].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x+1, y);
				}
				else if (8 <= map_level[level][x + 1][y] && map_level[level][x + 1][y] <= 11) {
					
					map_level[level][x + 1][y]--;
					int sugar_index = map.sugar[x + 1][y].GetFrameIndexOfBitmap();
					map.sugar[x + 1][y].SetFrameIndexOfBitmap(sugar_index - 1);
				}
			}
			if (0 <= y - 1 && y - 1 < 10) {
				if (6 <= map_level[level][x][y - 1] && map_level[level][x][y - 1] <= 7) {
					if (map_level[level][x][y - 1] == 6) {
						step_has_chocolate_destory = true;
					}
					map_level[level][x][y - 1] = 1;
					map.candy[x][y - 1].SetFrameIndexOfBitmap(0);
					effectlevel.shine(x, y-1);
					
				}
				else if (8 <= map_level[level][x][y - 1] && map_level[level][x][y - 1] <= 11) {
					map_level[level][x][y - 1] --;
					int sugar_index = map.sugar[x][y - 1].GetFrameIndexOfBitmap();
					map.sugar[x][y - 1].SetFrameIndexOfBitmap(sugar_index - 1);
				}
			}
		}
		void color_ball(int level) {
			if (map.candy[clickX][clickY].GetFrameIndexOfBitmap() == 25 && map.candy[changeX][changeY].GetFrameIndexOfBitmap() == 25) {
				for (int k = 0; k < 10; k++) {
					for (int k1 = 0; k1 < 10; k1++) {
						if (map.none_map(k, k1, level) || map.Chocolate_Machine.is_chocolate_machine(k, k1, level)) {
							continue;
						}
						object_element(k, k1, level, 0);
					}
				}
			}
			if (map.candy[clickX][clickY].GetFrameIndexOfBitmap() == 25) {
				for (int k = 0; k < 10; k++) {
					for (int z = 0; z < 10; z++) {
						if (map.none_map(k, z, level)) {
							continue;
						}
						if ((k == changeX && z == changeY) || (k == clickX && z == clickY)) {
							continue;
						}
						if ((map.Candy.is_candy(k, z, level, map.candy) || map.Bomb.is_bomb(k, z, level) || map.X_Block.is_x_block(k, z, level) || map.Glass.is_glass(k, z, level)) && is_object_same_color(k, z, changeX, changeY, level)) {
							object_element(k, z, level, 0);
						}
					}
				}
				map.candy[clickX][clickY].SetFrameIndexOfBitmap(0);
				Goal.SetGoal(25);
				object_element(changeX, changeY, level, 0);
				
			}
			else if (map.candy[changeX][changeY].GetFrameIndexOfBitmap() == 25) {
				for (int k = 0; k < 10; k++) {
					for (int z = 0; z < 10; z++) {
						if (map.none_map(k, z, level)) {
							continue;
						}
						if ((k == changeX && z == changeY) || (k == clickX && z == clickY)) {
							continue;
						}
						if ((map.Candy.is_candy(k, z, level, map.candy) || map.Bomb.is_bomb(k, z, level) || map.X_Block.is_x_block(k, z, level) || map.Glass.is_glass(k, z, level)) && is_object_same_color(k, z, clickX, clickY, level)) {
							object_element(k, z, level, 0);
						}
					}
				}
				map.candy[changeX][changeY].SetFrameIndexOfBitmap(0);
				Goal.SetGoal(25);
				object_element(clickX, clickY, level, 0);
			}
		}
		int get_color(int x, int y, int level) {
			int color_num = 0;
			if (map.candy[x][y].GetFrameIndexOfBitmap() > 6) {
				if (map.candy[x][y].GetFrameIndexOfBitmap() % 3 == 0) {
					color_num = (int)ceil((map.candy[x][y].GetFrameIndexOfBitmap() - 6) / 3);
				}
				else {
					color_num = (int)ceil((map.candy[x][y].GetFrameIndexOfBitmap() - 6) / 3) + 1;
				}
			}
			else {
				color_num = map.candy[x][y].GetFrameIndexOfBitmap();
			}
			return color_num;
		}
		void check_cherry_element(int level) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 3 && i== map.map_bottom(i, j, level)) {
						map.cherry[i][j].cherry_element(i, j, level);
						Goal.SetGoal(2);
						object_down(level);
					}
				}
			}
		}
		Step Step;
		Goal Goal;
		Score Score;
		Effect effectlevel;
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
		bool step_has_chocolate_destory ;
		CSpecialEffect time;
		int test = 0;
		int test1 = 0;
		int test2 = 0;
		int test3 = 0;
		bool visited[10][10] = {
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0} };
		int pre_map_level[10][10];
	};
}


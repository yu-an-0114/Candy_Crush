
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
#include "Bomb.h"
#include "Chocolate.h"
#include "ChocolatMachine.h"
#include "Glass.h"
#include "Sugar.h"
#include "X_block.h"
using namespace std;

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
						candy_lattice[i][j].LoadBitmapByString({ "resources/CandyLattice.bmp" });
						candy_lattice[i][j].SetTopLeft(10 + unit_candy_lattice.GetWidth()*j, 150 + unit_candy_lattice.GetHeight()*i);
						bomb[i][j].LoadBitmapByString({ "resources/candy/white.bmp","resources/bomb/yellow-bomb.bmp","resources/bomb/blue-bomb.bmp" ,"resources/bomb/red-bomb.bmp" ,"resources/bomb/purple-bomb.bmp" ,"resources/bomb/green-bomb.bmp" ,"resources/bomb/orange-bomb.bmp" }, RGB(255, 255, 255));
						bomb[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (unit_candy_lattice.GetWidth() - bomb[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (unit_candy_lattice.GetHeight() - bomb[i][j].GetHeight()) / 2);
						candy[i][j].LoadBitmapByString({ "resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp","resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp" }, RGB(255, 255, 255));				
						candy[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (unit_candy_lattice.GetWidth() - candy[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (unit_candy_lattice.GetHeight() - candy[i][j].GetHeight()) / 2);
						candy[i][j].SetFrameIndexOfBitmap(0);
						cherry[i][j].LoadBitmapByString({ "resources/cherry.bmp" }, RGB(255, 255, 255));
						cherry[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (unit_candy_lattice.GetWidth() - cherry[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (unit_candy_lattice.GetHeight() - cherry[i][j].GetHeight()) / 2);
						chocolate[i][j].LoadBitmapByString({ "resources/block/chocolate.bmp" }, RGB(255, 255, 255));
						chocolate[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (unit_candy_lattice.GetWidth() - chocolate[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (unit_candy_lattice.GetHeight() - chocolate[i][j].GetHeight()) / 2);
						chocolate_machine[i][j].LoadBitmapByString({ "resources/block/chocolate_machine.bmp" }, RGB(255, 255, 255));
						chocolate_machine[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (unit_candy_lattice.GetWidth() - chocolate_machine[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (unit_candy_lattice.GetHeight() - chocolate_machine[i][j].GetHeight()) / 2);
						glass[i][j].LoadBitmapByString({ "resources/block/glass.bmp","resources/block/glass2.bmp" }, RGB(255, 255, 255));
						glass[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (unit_candy_lattice.GetWidth() - glass[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (unit_candy_lattice.GetHeight() - glass[i][j].GetHeight()) / 2);
						sugar[i][j].LoadBitmapByString({ "resources/block/sugar.bmp","resources/block/sugar2.bmp","resources/block/sugar3.bmp","resources/block/sugar4.bmp","resources/block/sugar5.bmp" }, RGB(255, 255, 255));
						sugar[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (unit_candy_lattice.GetWidth() - sugar[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (unit_candy_lattice.GetHeight() - sugar[i][j].GetHeight()) / 2);
						x_block[i][j].LoadBitmapByString({"resources/block/X_block.bmp" }, RGB(255, 255, 255));
						x_block[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (unit_candy_lattice.GetWidth() - x_block[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (unit_candy_lattice.GetHeight() - x_block[i][j].GetHeight()) / 2);
						
						if (map_level[level][i][j] == 1) {
							candy[i][j].set_candy_random(i, j, level, candy);
						}
						else if (map_level[level][i][j] == 2) {
							candy[i][j].set_candy_random(i, j, level, candy);
						}
						else if (map_level[level][i][j] == 4) {
							bomb[i][j].set_bomb_random(i, j, level, bomb);
						}
						else if (map_level[level][i][j] == 7) {
							sugar[i][j].SetFrameIndexOfBitmap(0);
						}
						else if (map_level[level][i][j] == 8) {
							sugar[i][j].SetFrameIndexOfBitmap(1);
						}
						else if (map_level[level][i][j] == 9) {
							sugar[i][j].SetFrameIndexOfBitmap(2);
						}
						else if (map_level[level][i][j] == 10) {
							sugar[i][j].SetFrameIndexOfBitmap(3);
						}
						else if (map_level[level][i][j] == 11) {
							sugar[i][j].SetFrameIndexOfBitmap(4);
						}
						else if (map_level[level][i][j] == 12) {
							candy[i][j].set_candy_random(i, j, level, candy);
							glass[i][j].SetFrameIndexOfBitmap(0);
						}
						else if (map_level[level][i][j] == 13) {
							candy[i][j].set_candy_random(i, j, level, candy);
							glass[i][j].SetFrameIndexOfBitmap(1);
						}
					}
				}
			}	
		}
		void show_map(int level) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 0) {
						continue;
					}				
					candy_lattice[i][j].ShowBitmap();
				}
			}
			
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map_level[level][i][j] == 0) {
						continue;
					}
					else {	
						if (map_level[level][i][j] == 1) {
							candy[i][j].ShowBitmap();
						}
						else {
							candy[i][j].UnshowBitmap();
						}
						if (map_level[level][i][j] == 2) {
							candy[i][j].ShowBitmap();
							x_block[i][j].ShowBitmap();
						}
						else {
							candy[i][j].UnshowBitmap();
							x_block[i][j].UnshowBitmap();
						}
						if (map_level[level][i][j] == 3) {
							cherry[i][j].ShowBitmap();
						}
						else {
							cherry[i][j].UnshowBitmap();
						}
						if (map_level[level][i][j] == 4) {
							bomb[i][j].ShowBitmap();
						}
						else {
							bomb[i][j].UnshowBitmap();
						}
						if (map_level[level][i][j] == 5) {
							chocolate_machine[i][j].ShowBitmap();
						}
						else {
							chocolate_machine[i][j].UnshowBitmap();
						}
						if (map_level[level][i][j] == 6) {
							chocolate[i][j].ShowBitmap();
						}
						else {
							chocolate[i][j].UnshowBitmap();
						}
						if (7 <= map_level[level][i][j] && map_level[level][i][j] <= 11) {
							sugar[i][j].ShowBitmap();
						}
						else {
							sugar[i][j].UnshowBitmap();
						}
						if (12 <= map_level[level][i][j] && map_level[level][i][j] <= 13) {
							glass[i][j].ShowBitmap();
							candy[i][j].ShowBitmap();
						}
						else {
							glass[i][j].UnshowBitmap();
							candy[i][j].UnshowBitmap();
						}
					}
				}
			}
		}
		/*
		template <typename T>
		void set_candy_lattice_center(int x, int y,T& object) {
			object[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - object[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - object[x][y].GetHeight()) / 2);
		}*/
		void set_candy_lattice_center(int x, int y,int level) {
			if (map_level[level][x][y] == 0) {
				return;
			}
			if (map_level[level][x][y] == 1) {
				candy[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - candy[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - candy[x][y].GetHeight()) / 2);
			}
			else if (map_level[level][x][y] == 2) {
				x_block[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - x_block[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - x_block[x][y].GetHeight()) / 2);
				candy[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - candy[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - candy[x][y].GetHeight()) / 2);
			}
			else if(map_level[level][x][y]==3) {
				cherry[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - cherry[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - cherry[x][y].GetHeight()) / 2);
			}
			else if (map_level[level][x][y] == 4) {
				bomb[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - bomb[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - bomb[x][y].GetHeight()) / 2);
			}
			else if (map_level[level][x][y] == 5) {
				chocolate_machine[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - chocolate_machine[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - chocolate_machine[x][y].GetHeight()) / 2);
			}
			else if (map_level[level][x][y] == 6) {
				chocolate[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - chocolate[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - chocolate[x][y].GetHeight()) / 2);
			}
			else if (7 <= map_level[level][x][y] && map_level[level][x][y] <= 11) {
				sugar[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - sugar[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - sugar[x][y].GetHeight()) / 2);
			}
			else if (12 <= map_level[level][x][y] && map_level[level][x][y] <= 13) {
				glass[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - glass[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - glass[x][y].GetHeight()) / 2);
				candy[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (unit_candy_lattice.GetWidth() - candy[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (unit_candy_lattice.GetHeight() - candy[x][y].GetHeight()) / 2);
			}
		}

		Bomb bomb[10][10];
		Chocolate chocolate[10][10];
		ChocolateMachine chocolate_machine[10][10];
		CandyLattice unit_candy_lattice;
		CandyLattice candy_lattice[10][10];	
		Candy candy[10][10];
		Cherry cherry[10][10];
		Glass glass[10][10];
		Sugar sugar[10][10];
		X_block x_block[10][10];		
		int test = 0;
	};
}


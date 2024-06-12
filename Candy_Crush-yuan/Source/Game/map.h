
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
			Candy_Lattice.LoadBitmapByString({ "resources/CandyLattice.bmp" });

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (none_map(i, j, level)) {
						continue;
					}
					else {

						candy_lattice[i][j].LoadBitmapByString({ "resources/CandyLattice.bmp" },RGB(255,255,255));
						candy_lattice[i][j].SetTopLeft(10 + Candy_Lattice.GetWidth()*j, 150 + Candy_Lattice.GetHeight()*i);
						bomb[i][j].LoadBitmapByString({ "resources/candy/white.bmp","resources/bomb/yellow-bomb.bmp","resources/bomb/blue-bomb.bmp" ,"resources/bomb/red-bomb.bmp" ,"resources/bomb/purple-bomb.bmp" ,"resources/bomb/green-bomb.bmp" ,"resources/bomb/orange-bomb.bmp" }, RGB(255, 255, 255));
						bomb[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (Candy_Lattice.GetWidth() - bomb[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (Candy_Lattice.GetHeight() - bomb[i][j].GetHeight()) / 2);
						candy[i][j].LoadBitmapByString({ "resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp","resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" ,"resources/candy/yellow-candy-row.bmp" ,"resources/candy/yellow-candy-col.bmp" ,"resources/candy/yellow-candy-pack.bmp","resources/candy/blue-candy-row.bmp" ,"resources/candy/blue-candy-col.bmp" ,"resources/candy/blue-candy-pack.bmp","resources/candy/red-candy-row.bmp" ,"resources/candy/red-candy-col.bmp","resources/candy/red-candy-pack.bmp","resources/candy/purple-candy-row.bmp" ,"resources/candy/purple-candy-col.bmp","resources/candy/purple-candy-pack.bmp","resources/candy/green-candy-row.bmp" ,"resources/candy/green-candy-col.bmp" ,"resources/candy/green-candy-pack.bmp","resources/candy/orange-candy-row.bmp" ,"resources/candy/orange-candy-col.bmp","resources/candy/orange-candy-pack.bmp" ,"resources/candy/color-ball.bmp" }, RGB(255, 255, 255));
						candy[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (Candy_Lattice.GetWidth() - candy[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (Candy_Lattice.GetHeight() - candy[i][j].GetHeight()) / 2);
						candy[i][j].SetFrameIndexOfBitmap(0);
						cherry[i][j].LoadBitmapByString({ "resources/cherry.bmp" }, RGB(255, 255, 255));
						cherry[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (Candy_Lattice.GetWidth() - cherry[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (Candy_Lattice.GetHeight() - cherry[i][j].GetHeight()) / 2);
						chocolate[i][j].LoadBitmapByString({ "resources/block/chocolate.bmp" }, RGB(255, 255, 255));
						chocolate[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (Candy_Lattice.GetWidth() - chocolate[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (Candy_Lattice.GetHeight() - chocolate[i][j].GetHeight()) / 2);
						chocolate_machine[i][j].LoadBitmapByString({ "resources/block/chocolate_machine.bmp" }, RGB(255, 255, 255));
						chocolate_machine[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (Candy_Lattice.GetWidth() - chocolate_machine[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (Candy_Lattice.GetHeight() - chocolate_machine[i][j].GetHeight()) / 2);
						glass[i][j].LoadBitmapByString({ "resources/block/glass.bmp","resources/block/glass2.bmp" }, RGB(255, 255, 255));
						glass[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (Candy_Lattice.GetWidth() - glass[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (Candy_Lattice.GetHeight() - glass[i][j].GetHeight()) / 2);
						sugar[i][j].LoadBitmapByString({ "resources/block/sugar.bmp","resources/block/sugar2.bmp","resources/block/sugar3.bmp","resources/block/sugar4.bmp","resources/block/sugar5.bmp" }, RGB(255, 255, 255));
						sugar[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (Candy_Lattice.GetWidth() - sugar[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (Candy_Lattice.GetHeight() - sugar[i][j].GetHeight()) / 2);
						x_block[i][j].LoadBitmapByString({ "resources/block/X_block.bmp" }, RGB(255, 255, 255));
						x_block[i][j].SetTopLeft(candy_lattice[i][j].GetLeft() + (Candy_Lattice.GetWidth() - x_block[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() + (Candy_Lattice.GetHeight() - x_block[i][j].GetHeight()) / 2);
						if (map_top(i, j, level) == i) {
							random_candy[j].LoadBitmapByString({ "resources/candy/white.bmp" ,"resources/candy/yellow-candy.bmp","resources/candy/blue-candy.bmp" ,"resources/candy/red-candy.bmp" ,"resources/candy/purple-candy.bmp" ,"resources/candy/green-candy.bmp" ,"resources/candy/orange-candy.bmp" }, RGB(255, 255, 255));
							random_candy[j].SetTopLeft(candy_lattice[i][j].GetLeft() + (Candy_Lattice.GetWidth() - candy[i][j].GetWidth()) / 2, candy_lattice[i][j].GetTop() - (Candy_Lattice.GetHeight() - candy[i][j].GetHeight()) / 2);
						}

						if (map_level[level][i][j] == 1) {
							Candy.set_candy_random(i, j, candy);
						}
						else if (X_Block.is_x_block(i, j, level)) {
							Candy.set_candy_random(i, j, candy);
						}
						else if (Bomb.is_bomb(i, j, level)) {
							Bomb.set_bomb_random(i, j, level, bomb);
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
							Candy.set_candy_random(i, j, candy);
							glass[i][j].SetFrameIndexOfBitmap(0);
						}
						else if (map_level[level][i][j] == 13) {
							Candy.set_candy_random(i, j, candy);
							glass[i][j].SetFrameIndexOfBitmap(1);
						}
					}
				}
			}
		}
		void show_map(int level) {
			for (int i = 0; i < 10; i++) {
				random_candy[i].ShowBitmap();
				for (int j = 0; j < 10; j++) {
					if (none_map(i, j, level)) {
						continue;
					}
					candy_lattice[i][j].ShowBitmap();
				}
			}

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (none_map(i, j, level)) {
						continue;
					}
					else {
						if (Candy.is_candy(i, j, level, candy)) {
							candy[i][j].ShowBitmap();
						}
						else {
							candy[i][j].UnshowBitmap();
						}
						if (X_Block.is_x_block(i, j, level)) {
							candy[i][j].ShowBitmap();
							x_block[i][j].ShowBitmap();
						}
						else {
							candy[i][j].UnshowBitmap();
							x_block[i][j].UnshowBitmap();
						}
						if (Cherry.is_cherry(i, j, level)) {
							cherry[i][j].ShowBitmap();
						}
						else {
							cherry[i][j].UnshowBitmap();
						}
						if (Bomb.is_bomb(i, j, level)) {
							bomb[i][j].ShowBitmap();
						}
						else {
							bomb[i][j].UnshowBitmap();
						}
						if (Chocolate_Machine.is_chocolate_machine(i, j, level)) {
							chocolate_machine[i][j].ShowBitmap();
						}
						else {
							chocolate_machine[i][j].UnshowBitmap();
						}
						if (Chocolate.is_chocolate(i, j, level)) {
							chocolate[i][j].ShowBitmap();
						}
						else {
							chocolate[i][j].UnshowBitmap();
						}
						if (Sugar.is_sugar(i, j, level)) {
							sugar[i][j].ShowBitmap();
						}
						else {
							sugar[i][j].UnshowBitmap();
						}
						if (Glass.is_glass(i, j, level)) {
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
		void set_candy_lattice_center(int x, int y, int level) {
			if (none_map(x, y, level)) {
				return;
			}
			if (map_level[level][x][y] == 1) {
				candy[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (Candy_Lattice.GetWidth() - candy[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (Candy_Lattice.GetHeight() - candy[x][y].GetHeight()) / 2);
			}
			else if (X_Block.is_x_block(x, y, level)) {
				x_block[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (Candy_Lattice.GetWidth() - x_block[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (Candy_Lattice.GetHeight() - x_block[x][y].GetHeight()) / 2);
				candy[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (Candy_Lattice.GetWidth() - candy[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (Candy_Lattice.GetHeight() - candy[x][y].GetHeight()) / 2);
			}
			else if (Cherry.is_cherry(x, y, level)) {
				cherry[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (Candy_Lattice.GetWidth() - cherry[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (Candy_Lattice.GetHeight() - cherry[x][y].GetHeight()) / 2);
			}
			else if (Bomb.is_bomb(x, y, level)) {
				bomb[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (Candy_Lattice.GetWidth() - bomb[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (Candy_Lattice.GetHeight() - bomb[x][y].GetHeight()) / 2);
			}
			else if (Chocolate_Machine.is_chocolate_machine(x, y, level)) {
				chocolate_machine[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (Candy_Lattice.GetWidth() - chocolate_machine[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (Candy_Lattice.GetHeight() - chocolate_machine[x][y].GetHeight()) / 2);
			}
			else if (Chocolate.is_chocolate(x, y, level)) {
				chocolate[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (Candy_Lattice.GetWidth() - chocolate[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (Candy_Lattice.GetHeight() - chocolate[x][y].GetHeight()) / 2);
			}
			else if (Sugar.is_sugar(x, y, level)) {
				sugar[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (Candy_Lattice.GetWidth() - sugar[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (Candy_Lattice.GetHeight() - sugar[x][y].GetHeight()) / 2);
			}
			else if (Glass.is_glass(x, y, level)) {
				glass[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (Candy_Lattice.GetWidth() - glass[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (Candy_Lattice.GetHeight() - glass[x][y].GetHeight()) / 2);
				candy[x][y].SetTopLeft(candy_lattice[x][y].GetLeft() + (Candy_Lattice.GetWidth() - candy[x][y].GetWidth()) / 2, candy_lattice[x][y].GetTop() + (Candy_Lattice.GetHeight() - candy[x][y].GetHeight()) / 2);
			}
		}
		bool none_map(int x, int y, int level) {
			return map_level[level][x][y] == 0;
		}
		int map_top(int row, int col, int level) {
			for (int i = row - 1; i >= 0; i--) {
				if (none_map(i, col, level)) {
					return i + 1;
				}
			}
			return 0;
		}
		int map_bottom(int row, int col, int level) {
			for (int i = row; i < 10; i++) {
				if (none_map(i, col, level)) {
					return i + 1;
				}
			}
			return 9;
		}
		bool is_empty(int x, int y, int level, Candy candy[10][10]) {
			if ((map_level[level][x][y] == 1 || map_level[level][x][y] == 12 || map_level[level][x][y] == 13) && candy[x][y].GetFrameIndexOfBitmap() == 0) {
				return true;
			}
			return false;
		}
		Bomb bomb[10][10];
		Chocolate chocolate[10][10];
		ChocolateMachine chocolate_machine[10][10];
		CandyLattice candy_lattice[10][10];
		Candy candy[10][10];
		Cherry cherry[10][10];
		Glass glass[10][10];
		Sugar sugar[10][10];
		X_block x_block[10][10];

		Candy random_candy[10];
		Bomb Bomb;
		Chocolate Chocolate;
		ChocolateMachine Chocolate_Machine;
		CandyLattice Candy_Lattice;
		Candy Candy;
		Cherry Cherry;
		Glass Glass;
		Sugar Sugar;
		X_block X_Block;

		int test = 0;
	};
}


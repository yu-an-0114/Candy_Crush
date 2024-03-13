
//#ifdef MAP_H
//#define MAP_H
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

namespace game_framework {
	class Map {
	public:
		void Build_map() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					map[i][j].LoadBitmapByString({ "resources/CandyLattice.bmp" });
					map[i][j].SetTopLeft(10 + map[0][0].GetWidth()*j, 150 + map[0][0].GetHeight()*i);
					int RandNum = rand() % 6 + 1;
					if (RandNum == 1) {
						candy[i][j].LoadBitmapByString({ "resources/candy/yellow-candy.bmp" }, RGB(255, 255, 255));
						candy[i][j].SetTopLeft(map[i][j].GetLeft() + 8, map[i][j].GetTop());
					}
					else if (RandNum == 2) {
						candy[i][j].LoadBitmapByString({ "resources/candy/blue-candy.bmp" }, RGB(255, 255, 255));
						candy[i][j].SetTopLeft(map[i][j].GetLeft() + 3, map[i][j].GetTop()+2);
					}
					else if (RandNum == 3) {
						candy[i][j].LoadBitmapByString({ "resources/candy/red-candy.bmp" }, RGB(255, 255, 255));
						candy[i][j].SetTopLeft(map[i][j].GetLeft() + 8, map[i][j].GetTop()+2);
					}
					else if (RandNum == 4) {
						candy[i][j].LoadBitmapByString({ "resources/candy/purple-candy.bmp" }, RGB(255, 255, 255));
						candy[i][j].SetTopLeft(map[i][j].GetLeft() + 4, map[i][j].GetTop()+2);
					}
					else if (RandNum == 5) {
						candy[i][j].LoadBitmapByString({ "resources/candy/green-candy.bmp" }, RGB(255, 255, 255));
						candy[i][j].SetTopLeft(map[i][j].GetLeft() + 6, map[i][j].GetTop()+1);
					}
					else if (RandNum == 6) {
						candy[i][j].LoadBitmapByString({ "resources/candy/orange-candy.bmp" }, RGB(255, 255, 255));
						candy[i][j].SetTopLeft(map[i][j].GetLeft() + 10, map[i][j].GetTop());
					}	
				}
			}
		}

		void Show_map() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					map[i][j].ShowBitmap();
					candy[i][j].ShowBitmap();
				}
			}
		}

		/*void Candy_Element() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					int k = 1;
					while (1) {
						if (candy[i][j].GetImageFileName != candy[i][j + k].GetImageFileName) {
							break;
						}
						k++;
					}

				}
			}
		}*/
		bool isClick_CMovingBitmap(CMovingBitmap obj, CPoint point) {
			return obj.GetLeft() < point.x && obj.GetLeft() + obj.GetWidth() > point.x && obj.GetTop() > point.y && obj.GetTop() - obj.GetHeight() < point.y;
		}
		/*void Candy_Move(CPoint point) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (candy[i][j].GetLeft()<)
				}
			}
			
		}*/
	private:
		CMovingBitmap map[10][10];
		CMovingBitmap candy[10][10];
	};
}
//#endif 

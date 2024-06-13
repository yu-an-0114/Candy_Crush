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
	class Chocolate : public CMovingBitmap {
	public:
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
									if (map_level[level][rand_x][rand_y + 1] == 1) {
										map_level[level][rand_x][rand_y + 1] = 6;
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
								if (0 <= rand_y - 1 && rand_y - 1 <= 10) {
									if (map_level[level][rand_x][rand_y - 1] == 1) {
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
		bool is_chocolate(int x, int y, int level) {
			return map_level[level][x][y] == 6;
		}
	private:

	};
}
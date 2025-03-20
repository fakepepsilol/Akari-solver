#pragma once
#include <cstring>
class Level {
public:
	Level(char* grid, int x, int y);
	Level(int x, int y);

	int   x;
	int   y;
	char* grid;
	void  print(bool noDots = false);
	void  fixEdge();
};

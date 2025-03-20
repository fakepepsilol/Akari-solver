#include "level.h"

#include <cstdio>

Level::Level(char* grid, int x, int y) {
	this->grid = grid;
	this->x    = x;
	this->y    = y;
};
Level::Level(int x, int y) { char* _grid = new char[(x + 2) * (y + 2) + 1](); };

void Level::print(bool noDots) {
	int i;
	for (int Y = 0; Y < this->y; Y++) {
		for (int X = 0; X < this->x; X++) {
			i = Y * this->x + X;
			printf("%c ", noDots ? ((this->grid[i] == '.') ? ' ' : this->grid[i]) : this->grid[i]);
		}
		printf("\n");
	}
}
void Level::fixEdge() {
	memset(grid, '#', x);
	for (int _ = 1; _ < y; _++) {
		grid[_ * x]         = '#';
		grid[_ * x + x - 1] = '#';
	}
	memset(grid + x * (y - 1), '#', x);
};

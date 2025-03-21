#include "level.h"

#include "position.h"

#include <cstdio>
#include <cstring>
#include <vector>

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
int Level::getNeighbors(Position pos, const char* targets) {
	std::vector<Position> offsets = {
		{ 1,  0},
		{-1,  0},
		{ 0,  1},
		{ 0, -1},
	};

	int ret = 0;

	int charsLen = strlen(targets);
	for (int i = 0; i < 4; i++) {
		for (int c = 0; c < charsLen; c++) {
			if (grid[(pos.y + offsets[i].y) * x + (pos.x + offsets[i].x)] == targets[c]) {
				ret++;
				break;
			}
		}
	}

	return ret;
}

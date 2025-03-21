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
	for (int Y = 0; Y < y; Y++) {
		for (int X = 0; X < x; X++) {
			i = Y * x + X;
			switch (grid[i]) {
			case '@': printf("\033[31m"); break;
			case '+': printf("\033[32m"); break;
			case '#': printf("\033[34m"); break;
			case 'X': printf("\033[92m"); break;
			}
			printf("%c", noDots ? ((grid[i] == '.') ? ' ' : grid[i]) : grid[i]);
			printf("\033[0m ");
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
Positions Level::getNeighbors(Position pos, const char* targets) {
	std::vector<Position> offsets = {
		{ 1,  0},
		{-1,  0},
		{ 0,  1},
		{ 0, -1},
	};

	Positions ret;

	int charsLen = strlen(targets);
	for (int i = 0; i < 4; i++) {
		for (int c = 0; c < charsLen; c++) {
			if (grid[(pos.y + offsets[i].y) * x + (pos.x + offsets[i].x)] == targets[c]) {
				ret.push_back({pos.x + offsets[i].x, pos.y + offsets[i].y});
				break;
			}
		}
	}

	return ret;
}
int Level::getNeighborCnt(Position pos, const char* targets) {
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
void Level::shineLight(Position pos) {
	int state = 0;
	int index = 0;
	int i     = 0;

	const char* passChars = ".+x";
	const char* stopChars = "XB01234#";

	int   len      = strlen(passChars) + strlen(stopChars) + 1;
	char* allChars = new char[len]();
	strcpy(allChars, passChars);
	strcat(allChars, stopChars);

	grid[pos.y * x + pos.x] = '@';

exit_loop:
	while (state != 4) {
		i = (!(state % 2) ? pos.x : pos.y);
		for (;; ((state < 2) ? i++ : i--)) {
			index = ((state % 2) ? (i * x + pos.x) : (pos.y * x + i));
			for (int chr = 0; chr < len; chr++) {
				if ((!(state % 2) ? (i < 0 || i >= x) : (i < 0 || i >= y))) {
					state++;
					goto exit_loop;
				}
				if (grid[index] == allChars[chr]) {
					if (chr < strlen(passChars)) {
						grid[index] = '+';
					} else {
						state++;
						goto exit_loop;
					}
				}
			}
		}
	}
}

#include "level.h"

#include "position.h"

#include <cstdio>
#include <cstring>
#include <vector>

Level::Level(char* grid, int x, int y) {
	this->x    = x;
	this->y    = y;
	this->grid = grid;
};
Level::Level(int x, int y) {
	this->x    = x;
	this->y    = y;
	this->grid = new char[(x + 2) * (y + 2) + 1]();
};
Level::Level(const Level& source) {
	x    = source.x;
	y    = source.y;
	grid = new char[(x + 2) * (y + 2) + 1]();
	memcpy(grid, source.grid, (x + 2) * (y + 2));
}

void Level::print(bool noDots) const {
	int i;
	for (int Y = 0; Y < y; Y++) {
		for (int X = 0; X < x; X++) {
			i = Y * x + X;
#ifndef _WIN32
			switch (grid[i]) {
			case '@': printf("\033[31m"); break;
			case '+': printf("\033[32m"); break;
			case '#': printf("\033[34m"); break;
			case 'X': printf("\033[93m"); break;
			case 'x': printf("\033[35m"); break;
			}
			printf("%c", noDots ? ((grid[i] == '.') ? ' ' : grid[i]) : grid[i]);
			printf("\033[0m ");
#else  // cmd doesn't support ANSI colors, skill issue
			printf("%c ", noDots ? ((grid[i] == '.') ? ' ' : grid[i]) : grid[i]);
#endif
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
	return getNeighbors(pos, targets).size();
	// std::vector<Position> offsets = {
	// 	{ 1,  0},
	// 	{-1,  0},
	// 	{ 0,  1},
	// 	{ 0, -1},
	// };
	//
	// int ret = 0;
	//
	// int charsLen = strlen(targets);
	// for (int i = 0; i < 4; i++) {
	// 	for (int c = 0; c < charsLen; c++) {
	// 		if (grid[(pos.y + offsets[i].y) * x + (pos.x + offsets[i].x)] == targets[c]) {
	// 			ret++;
	// 			break;
	// 		}
	// 	}
	// }
	//
	// return ret;
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

	grid[pos.y * x + pos.x]   = '@';
	Positions neighborOffsets = {
		{-1,  0},
		{ 1,  0},
		{ 0, -1},
		{ 0,  1}
  };
	for (int i = 0; i < 4; i++) {
		Position tempPos   = {pos.x + neighborOffsets[i].x, pos.y + neighborOffsets[i].y};
		char     tile      = grid[tempPos.y * x + tempPos.x];
		int      tileValue = tile - '0';
		if (tile >= '0' && tile <= '4') {
			if (getNeighborCnt(tempPos, "@") == tileValue) { setTileAsSolved(tempPos); }
		}
	}

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
void Level::setTileAsSolved(Position pos) {
	grid[pos.y * x + pos.x] = 'X';
	for (Position neighbor : getNeighbors(pos, ".")) {
		grid[neighbor.y * x + neighbor.x] = 'x';
	}
}

Positions Level::getVisible(Position pos, const char* targets, const char* stopChars) {
	Positions ret;
	int       state = 0;
	int       index = 0;
	int       i     = 0;

	int   len      = strlen(targets) + strlen(stopChars) + 2;
	char* allChars = new char[len]();
	strcpy(allChars, targets);
	strcat(allChars, stopChars);
	allChars[len - 2] = '#';

	// grid[pos.y * x + pos.x] = '@';

exit_loop:
	while (state != 4) {
		i = (!(state % 2) ? pos.x : pos.y);
		for (;; ((state < 2) ? i++ : i--)) {
			// Y * x + X
			int X = ((state % 2) ? pos.x : i);
			int Y = ((state % 2) ? i : pos.y);
			if (Position{X, Y} == pos) { continue; }
			index = Y * x + X;
			for (int chr = 0; chr < len; chr++) {
				if ((!(state % 2) ? (i < 0 || i >= x) : (i < 0 || i >= y))) {
					state++;
					goto exit_loop;
				}
				if (grid[index] == allChars[chr]) {
					if (chr < strlen(targets)) {
						ret.push_back({X, Y});
						// grid[index] = '+';
					} else {
						state++;
						goto exit_loop;
					}
				}
			}
		}
	}
	return ret;
}
bool Level::isValidMove(Position pos) {

	Level newLevel = Level(*this);
	newLevel.shineLight(pos);

	for (int X = 1; X < x - 1; X++) {
		for (int Y = 1; Y < y - 1; Y++) {
			char tile = newLevel.grid[Y * x + X];
			if (tile >= '0' && tile <= '4') {
				int tileValue = tile - '0';
				if ((tileValue - newLevel.getNeighborCnt({X, Y}, "@"))
				    > newLevel.getNeighborCnt({X, Y}, ".")) {
					return false;
				}
			}
			if (tile == 'x' && (newLevel.getVisible({X, Y}, ".").size() == 0)) { return false; }
		}
	}

	return true;
}

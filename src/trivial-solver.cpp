#include "level.h"
#include "position.h"

#include <cstdio>

void Level::trivialSolve() {
	int index;
	for (int X = 0; X < x; X++) {
		for (int Y = 0; Y < y; Y++) {
			index = Y * x + X;
			if (grid[index] - '0' == getNeighborCnt({X, Y}, ".")) {
				grid[index] = 'X';
				for (Position pos : getNeighbors({X, Y}, ".")) {
					shineLight(pos);
				}
			}
		}
	}
}

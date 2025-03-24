#include "level.h"
#include "position.h"

#include <cstdio>

void Level::trivialSolve() {
	int  index;
	int  iteration = 0;
	bool changed   = true;
	while (changed) {
		changed = false;
		for (int X = 0; X < x; X++) {
			for (int Y = 0; Y < y; Y++) {
				index           = Y * x + X;
				char* tile      = &grid[index];
				int   tileValue = grid[index] - '0';
				if (tileValue < 0 || tileValue > 4) { continue; }

				// number of neighboring lightbulbs
				int lightbulbCnt = getNeighborCnt({X, Y}, "@");
				int freeSpaceCnt = getNeighborCnt({X, Y}, ".");
				int missingBulbs = tileValue - lightbulbCnt;
				if (missingBulbs < 0) {
					// self explainatory
					printf("The trivial solver fucked up!\n");
					return;
				}
				if (missingBulbs == 0) {
					setTileAsSolved({X, Y});
					changed = true;
					continue;
				}
				if (missingBulbs == freeSpaceCnt) {
					for (Position pos : getNeighbors({X, Y}, ".")) {
						shineLight(pos);
					}
					setTileAsSolved({X, Y});
					changed = true;
					continue;
				}


				// if (grid[index] - '0' == getNeighborCnt({X, Y}, ".")) {
				// 	grid[index] = 'X';
				// 	for (Position pos : getNeighbors({X, Y}, ".")) {
				// 		shineLight(pos);
				// 	}
				// }
			}
		}
	}
}

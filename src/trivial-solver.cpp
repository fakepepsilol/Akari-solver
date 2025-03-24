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
				index              = Y * x + X;
				char*    tilePtr   = &grid[index];
				char     tile      = *tilePtr;
				int      tileValue = tile - '0';
				Position pos       = {X, Y};
				if (tile == 'x' || tile == '.') {
					Positions emptySpaces = getVisible(pos, ".");
					bool      wrongTile   = false;

					wrongTile = ((tile == 'x' && (emptySpaces.size() != 1))
					             || ((tile == '.') && (emptySpaces.size() != 0)));
					if (!wrongTile) {
						if (tile == '.') {
							shineLight(pos);
						} else {
							shineLight(emptySpaces[0]);
						}
						changed = true;
						continue;
					}
				}

				if (tileValue < 0 || tileValue > 4) { continue; }

				// number of neighboring lightbulbs
				int lightbulbCnt = getNeighborCnt(pos, "@");
				int freeSpaceCnt = getNeighborCnt(pos, ".");
				int missingBulbs = tileValue - lightbulbCnt;
				if (missingBulbs < 0) {
					// self explainatory
					printf("The trivial solver fucked up!\n");
					return;
				}
				if (missingBulbs == 0) {
					setTileAsSolved(pos);
					changed = true;
					continue;
				}
				if (missingBulbs == freeSpaceCnt) {
					for (Position pos : getNeighbors(pos, ".")) {
						shineLight(pos);
					}
					setTileAsSolved(pos);
					changed = true;
					continue;
				}


				// if (grid[index] - '0' == getNeighborCnt(pos, ".")) {
				// 	grid[index] = 'X';
				// 	for (Position pos : getNeighbors(pos, ".")) {
				// 		shineLight(pos);
				// 	}
				// }
			}
		}
	}
}

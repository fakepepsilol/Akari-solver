#include "level.h"
#include "position.h"

#include <cstdio>
bool _isValidMove(const Level& level, Position pos);

void Level::trivialSolve() {
	int  index;
	int  iteration = 0;
	bool changed   = true;
	while (changed) {
		changed = false;
		for (int X = 1; X < x - 1; X++) {
			for (int Y = 1; Y < y - 1; Y++) {
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
				if (tile != 'x' && tile != 'X' && (tile < '0' || tile > '4') && tile != 'B') {
					// TEST

					if (!isValidMove(pos)) {
						grid[Y * x + X] = 'x';
						changed         = true;
					}

					// TEST
				}
				if (tileValue < 0 || tileValue > 4) { continue; }

				// number of neighboring lightbulbs
				int lightbulbCnt = getNeighborCnt(pos, "@");
				// number of neighboring free spaces
				int freeSpaceCnt = getNeighborCnt(pos, ".");
				// number of lightbulbs to be placed
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

				if (missingBulbs < freeSpaceCnt) {
					// printf("(%d, %d) -> needs: %d; free spaces: %d\n", X, Y, missingBulbs, freeSpaceCnt);
					// print();
					Positions freeNeighbors = getNeighbors(pos, ".");
					for (Position fNpos : freeNeighbors) {
						if (!isValidMove(fNpos)) {
							grid[fNpos.y * x + fNpos.x] = 'x';
							freeSpaceCnt--;
							changed = true;
						}
					}
					if (freeSpaceCnt == missingBulbs) {
						for (Position fNpos : getNeighbors(pos, ".")) {
							shineLight(fNpos);
						}
						setTileAsSolved(pos);
					}
				}
			}
		}
		// printf("%d:\n", iteration);
		// print();
		// printf("\n\n");
		iteration++;
	}
	// isValidMove(*this, {1, 1});
}
bool Level::isSolved() {
	char tile;
	for (int X = 1; X < x; X++) {
		for (int Y = 1; Y < y; Y++) {
			tile = grid[Y * x + X];
			if (tile == '.' || tile == 'x' || (tile >= '0' && tile <= '4')) { return false; }
		}
	}

	return true;
}
bool _isValidMove(const Level& originalLevel, Position pos) {
	Level newLevel = Level(originalLevel);
	newLevel.shineLight(pos);
	int   index;
	char* grid = newLevel.grid;

	for (int X = 1; X < newLevel.x - 1; X++) {
		for (int Y = 1; Y < newLevel.y - 1; Y++) {
			index = Y * newLevel.x + X;
			if (grid[index] < '0' || grid[index] > '4') { continue; }
			if ((grid[index] - '0' - newLevel.getNeighborCnt({X, Y}, "@"))
			    > newLevel.getNeighborCnt({X, Y}, ".")) {
				// printf("------- (%d, %d) returning false because of: (%d, %d)\n", pos.x, pos.y, X, Y);
				return false;
			}
		}
	}

	return true;
}

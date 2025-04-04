#include "level.h"
#include "position.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

int factorial(int n) {
	unsigned long long result = 1;
	for (int i = 1; i <= n; i++) {
		result *= i;
	}
	return result;
}

ChoicesPerTile Level::getChoicesPerTile(Position pos) {
	ChoicesPerTile ret;

	int tileValue = grid[pos.y * x + pos.x] - '0';
	if (tileValue < 0 || tileValue > 4) { return ret; }

	Positions emptyNeighbors = getNeighbors(pos, ".");

	// (n) choose k
	int emptyNeigborCnt = emptyNeighbors.size();

	// n choose (k)
	int chooseCnt = tileValue - getNeighborCnt(pos, "@");

	int n = emptyNeigborCnt;
	int k = chooseCnt;

	std::vector<bool> bitmask(k, true);
	bitmask.resize(n, false);

	do {
		Positions subset;
		for (int i = 0; i < n; i++) {
			if (bitmask[i]) { subset.push_back(emptyNeighbors[i]); }
		}
		ret.choices.push_back(subset);
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));
	// printf("returning ret.size() -> %ld\n", ret.choices.size());
	ret.tilePosition = pos;
	return ret;
}
Choices Level::getChoices() {
	Choices        ret;
	ChoicesPerTile temp;
	for (int X = 1; X < x - 1; X++) {
		for (int Y = 1; Y < y - 1; Y++) {
			temp = getChoicesPerTile({X, Y});
			if (temp.choices.size() > 0) { ret.push_back(temp); }
		}
	}

	return ret;
}

int Level::getNumFreeTiles() {
	int ret;

	for (int X = 1; X < x - 1; X++) {
		for (int Y = 1; Y < y - 1; Y++) {
			ret++;
		}
	}

	return ret;
}
Level* lowestLvl;

void Level::backtracker(Choices& choices, int depth = 0) {
	if (depth == choices.size()) { return; }
	// printf("\n%d: ", depth);
	for (Positions poss : choices[depth].choices) {
		Level newLevel = Level(*this);
		bool  failed   = false;
		for (Position pos : poss) {
			if (newLevel.isValidMove(pos)) {
				newLevel.shineLight(pos);
			} else {
				goto failed;
			}
			// printf("%d|%d->(%d, %d), ",
			//        choices[depth].tilePosition.x,
			//        choices[depth].tilePosition.y,
			//        pos.x,
			//        pos.y);
		}
		newLevel.trivialSolve();
		newLevel.backtracker(choices, depth + 1);
		if (newLevel.isSolved()) { memcpy(grid, newLevel.grid, x * y); }
	failed:
		continue;
	}
}

void Level::backtrackSolve() {
	printf("backtrack solver --- ");
	Choices choices = getChoices();
	printf("choice count: %ld\n", choices.size());
	backtracker(choices);
	// ChoicesPerTile cpt = choices[depth];
	// for (ChoicesPerTile cpt : choices) {
	//   printf("For tile: %d, %d -> {", cpt.tilePosition.x, cpt.tilePosition.y);
	//   for (Positions poss : cpt.choices) {
	//     for (Position pos : poss) {
	//       printf("(%d, %d), ", pos.x, pos.y);
	//     }
	//   }
	//   printf("\b\b}\n");
	// }
	return;


	for (ChoicesPerTile comb : choices) {
		for (Positions poss : comb.choices) {
			// printf("{");
			Level newLevel = Level(*this);
			for (Position pos : poss) {
				if (!newLevel.isValidMove(pos)) {
					// printf("invalid choice for tile\n");
					break;
				}
				newLevel.shineLight(pos);
				printf("(%d, %d), ", pos.x, pos.y);
				// newLevel.setTileAsSolved(comb.tilePosition);

				newLevel.trivialSolve();
				if (newLevel.isSolved()) {
					memcpy(grid, newLevel.grid, x * y);
					// newLevel.print();
					return;
				}
				// printf("(%d, %d), ", pos.x, pos.y);
			}
			if (!lowestLvl) {
				lowestLvl = &newLevel;
			} else {
				lowestLvl =
						(newLevel.getNumFreeTiles() < lowestLvl->getNumFreeTiles() ? &newLevel : lowestLvl);
			}
			printf("\n");
			// printf("\b\b}, ");
		}
		// printf("\b\b \n");
	}
	if (lowestLvl) { lowestLvl->print(); }
}

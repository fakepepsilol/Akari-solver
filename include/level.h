#pragma once
#include "position.h"
#include "tests.h"

#include <string>

class Level {
public:
	Level(char* grid, int x, int y);
	Level(int x, int y);
	Level(const Level&);

	// src/level.cpp
	void print(bool noDots = false) const;

	// src/trivial-solver.cpp
	void        trivialSolve();
	void        backtrackSolve();
	bool        isSolved();
	std::string getSolveCommand();

private:
	// if you have to access these, you're
	// probably doing something wrong
	int   x;
	int   y;
	char* grid;

	// Position -> struct{int x; int y;};
	// Positions -> std::vector<Position>
	// SE -> self explainatory


	// src/level.cpp
	void fixEdge();                  // SE
	void shineLight(Position);       // SE - don't even attempt to understand this
	void setTileAsSolved(Position);  // SE
	void backtracker(Choices& choices, int depth);

	// src/level.cpp
	bool isValidMove(Position pos, bool quick = false);
	bool emptyBacktracker();


	int getNeighborCnt(Position, const char* targets);  // SE

	// src/backtracker.cpp
	int getNumFreeTiles();

	// returns positions of neighbors that match
	// at least one character from 'targets'
	// example: getNeighbors({4, 5}, ".+x");
	// returns neighbors that are '.' or '+' or 'x'
	Positions getNeighbors(Position, const char* targets);

	// returns positions of tiles that are visible
	// from the Position, provided that they match
	// a character from 'targets'. Stops at any of
	// the 'stopChars', i.e. continues into the next
	// direction.
	Positions getVisible(Position, const char* targets, const char* stopChars = "B@01234X#");

	// returns a vector of the 'Positions' type,
	// meaning valid choices for bulb placements
	// example: a tile (x: 2, y: 2) needs 2 bulbs,
	// but has all 4 empty neighbors:
	// returns:
	// {
	// combination 1: {bulb1: (2, 1), bulb2: (3, 2)},
	// combination 2: {bulb1: (3, 2), bulb2: (2, 3)},
	// ...
	// }
	// (basically n-Choose-k but with Positions)
	// src/backtracker.cpp
	ChoicesPerTile getChoicesPerTile(Position pos);

	// returns a vector of return values from
	// getCombinationsForTile for the level
	Choices getChoices();


	// grant test functions access to the private fields and methods
	friend bool Tests::_test_fixEdge();
	friend bool Tests::_test_getNeighbors();
	friend bool Tests::_test_getNeighborCnt();
	friend bool Tests::_test_getVisible();
	friend bool Tests::_test_getCombinationsForTile();
	friend bool _isValidMove(const Level&, Position);
};
// src/level.cpp

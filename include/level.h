#pragma once
#include "position.h"
#include "tests.h"
class Level {
public:
	Level(char* grid, int x, int y);
	Level(int x, int y);
	Level(const Level&);

	// src/level.cpp
	void print(bool noDots = false) const;

	// src/trivial-solver.cpp
	void trivialSolve();
	bool isSolved();

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


	int getNeighborCnt(Position, const char* targets);  // SE

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

	// grant test functions access to the private fields and methods
	friend bool Tests::_test_fixEdge();
	friend bool Tests::_test_getNeighbors();
	friend bool Tests::_test_getNeighborCnt();
	friend bool Tests::_test_getVisible();
	friend bool isValidMove(const Level&, Position);
};
// src/level.cpp

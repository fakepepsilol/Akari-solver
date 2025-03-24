#pragma once
#include "position.h"
#include "tests.h"


class Level {
public:
	Level(char* grid, int x, int y);
	Level(int x, int y);

	// src/level.cpp
	void print(bool noDots = false);

	// src/trivial-solver.cpp
	void trivialSolve();

private:
	int   x;
	int   y;
	char* grid;

	// src/level.cpp

	void fixEdge();
	void shineLight(Position);
	void setTileAsSolved(Position);


	int getNeighborCnt(Position, const char* targets);

	Positions getNeighbors(Position, const char* targets);


	// grant access to the private fields and methods
	friend bool Tests::_test_fixEdge();
	friend bool Tests::_test_getNeighbors();
	friend bool Tests::_test_getNeighborCnt();
};
// src/level.cpp

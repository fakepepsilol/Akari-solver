#pragma once
#include "position.h"

class Level {
public:
	Level(char* grid, int x, int y);
	Level(int x, int y);

	int   x;
	int   y;
	char* grid;
	// src/level.cpp
	void print(bool noDots = false);
	void fixEdge();

	Positions getNeighbors(Position, const char* targets);
	int       getNeighborCnt(Position, const char* targets);

	void shineLight(Position);

	// src/trivial-solver.cpp
	void trivialSolve();
};
// src/level.cpp

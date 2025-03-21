#pragma once
#include "position.h"

class Level {
public:
	Level(char* grid, int x, int y);
	Level(int x, int y);

	int   x;
	int   y;
	char* grid;
	void  print(bool noDots = false);
	void  fixEdge();
	int   getNeighbors(Position, const char* targets);
	void  trivialSolve();
};
// src/level.cpp

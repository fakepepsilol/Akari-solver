#include "level.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
inline int _stoi(std::string in) {
	int                ret;
	std::istringstream ss(in);
	ss >> ret;
	return ret;
}
Level CurlToLevel(std::string in) {
	if (in.find("ggSDK.embed(") == -1) {
		std::cerr << "Failed to read request. (wrong url?)";
		exit(1);
	}
	in = in.substr(in.find("ggSDK.embed("));
	in = in.substr(0, in.find('\n') - 3);
	for (int i = in.length() - 2; i > 0; i--) {
		if (in[i] == '\'') {
			in = in.substr(i);
			break;
		}
	}


	std::string xStr;
	std::string yStr;

	bool first = true;
	for (int i = 1; i < in.length() - 1; i++) {
		if (in[i] == '|') {
			if (!first) { break; }
			first = false;
			continue;
		}
		(first ? xStr : yStr) += in[i];
	}


	in = in.substr(xStr.length() + yStr.length() + 3);
	in = in.substr(0, in.length() - 1);


	int x = _stoi(xStr);
	int y = _stoi(yStr);

	int   gridSize = (x + 2) * (y + 2);
	char* grid     = new char[gridSize + 1]();
	memset(grid, '#', gridSize);
	for (int Y = 0; Y < y; Y++) {
		memcpy(&grid[(Y + 1) * (x + 2) + 1], &in[Y * x], x);
	}
	Level level(grid, x + 2, y + 2);
	return level;
}

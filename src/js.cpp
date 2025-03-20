#include "level.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
inline int _stoi(std::string in) {
	int                ret;
	std::istringstream ss(in);
	ss >> ret;
	return ret;
}
Level CurlToLevel(std::string in) {
	std::regex  pattern("'(\\d{1,2})\\|(\\d{1,2})\\|(.+)'");
	std::smatch match;
	std::regex_search(in, match, pattern);
	if (match.empty()) {
		std::cerr << "Failed to read request. (wrong url?)";
		exit(1);
	}
	std::string js      = match.str(3);
	const char* js_cstr = js.c_str();

	int x = _stoi(match.str(1));
	int y = _stoi(match.str(2));
	printf("x: %d\ny: %d\n", x, y);
	char* grid = new char[(x + 2) * (y + 2) + 1]();
	memset(grid, '#', (x + 2) * (y + 2));
	Level level(grid, x + 2, y + 2);
	for (int Y = 0; Y < y; Y++) {
		memcpy(&grid[(Y + 1) * level.x + 1], &js_cstr[Y * x], x);
	}
	level.fixEdge();

	return level;
}

#include "level.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

// inline int _stoi(std::string in) {
// 	int                ret;
// 	std::istringstream ss(in);
// 	ss >> ret;
// 	return ret;
// }
Level CurlToLevel(std::string in) {
	if (in.find("ggSDK.embed(") == -1) {
		std::cerr << "Failed to read request. (wrong url?)\n";
		exit(1);
	}
	in = in.substr(in.find("ggSDK.embed("));

	std::string xStr;
	std::string yStr;

	in = in.substr(0, in.find("\n"));  // for the goofy ahh format


	bool first = true;
	in         = in.substr(in.find("sx: ") + 4);
	for (int i = 0; i < in.length() - 1; i++) {
		if (in[i] == ',') {
			if (!first) { break; }
			first = false;
			i    += 5;
			continue;
		}
		(first ? xStr : yStr) += in[i];
	}

	in = in.substr(in.find("'") + 1);
	if (in.find("|") != std::string::npos) {
		// printf("normal ahh format: | at %ld\n", in.find("|"));
		in = in.substr(xStr.length() + yStr.length() + 2);
	} else {
		// printf("goofy ahh format\n");
		for (int i = 0; i < in.length() - 1; i++) {
			switch (in[i]) {
			case '*': in[i] = '@'; break;
			case '#': in[i] = 'B'; break;
			case '.': in[i] = '+'; break;
			}
		}
	}


	int x = std::__cxx11::stoi(xStr);
	int y = std::__cxx11::stoi(yStr);
	in    = in.substr(0, x * y);

	int   gridSize = (x + 2) * (y + 2);
	char* grid     = new char[gridSize + 1]();
	memset(grid, '#', gridSize);
	for (int Y = 0; Y < y; Y++) {
		memcpy(&grid[(Y + 1) * (x + 2) + 1], &in[Y * x], x);
	}
	Level level(grid, x + 2, y + 2);
	return level;
}

#include "https.h"
#include "js.h"

#include <cstdio>
#include <cstdlib>
#include <string>
int main(int argc, char* argv[]) {
	std::string url  = inputUrl(argc, argv);
	std::string curl = runCurl(url);

	Level level = CurlToLevel(curl);
	// level.print(true);
	level.trivialSolve();
	if (!level.isSolved()) {
		if (argc == 3) {
			printf("no backtracker :\(\n");
		} else {
			printf("backtracker..\n");
			level.backtrackSolve();
			// printf("\n");
		}
	}
	level.print();
	if (level.isSolved()) {
		printf("Solved!\n\n");
		printf("-----\n%s\n-----", level.getSolveCommand().c_str());
	} else {
		printf("Failed!\n\n");
	}
	// level.print();
	return 0;
}

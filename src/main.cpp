#include "https.h"
#include "js.h"

#include <cstdio>
#include <string>
int main(int argc, char* argv[]) {
	std::string url  = inputUrl(argc, argv);
	std::string curl = runCurl(url);

	Level level = CurlToLevel(curl);
	level.print(true);
	level.trivialSolve();
	// level.backtrackSolve();
	if (level.isSolved()) {
		level.print();
		printf("Solved!\n\n");
		return 0;
	}
	level.print();
	printf("Failed.\n\n");
	// level.print();
	return 0;
}

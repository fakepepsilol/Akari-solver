#include "https.h"
#include "js.h"

#include <cstdio>
#include <string>
int main() {
	std::string url  = inputUrl();
	std::string curl = runCurl(url);

	Level level = CurlToLevel(curl);
	printf("\n");
	// level.print();
	level.trivialSolve();
	if (level.isSolved()) {
		level.print();
		printf("Solved!\n");
		return 0;
	}
	level.print();
	return 0;
}

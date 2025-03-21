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
	level.print();
	return 0;
}

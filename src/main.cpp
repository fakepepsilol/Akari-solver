#include "https.h"
#include "js.h"

#include <cstdio>
#include <string>
int main() {
	std::string url  = inputUrl();
	std::string curl = runCurl(url);

	Level level = CurlToLevel(curl);
	level.print();
	printf("-> %d <-\n", level.getNeighbors({1, 1}, ".#"));

	return 0;
}

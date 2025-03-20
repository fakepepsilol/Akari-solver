#include "https.h"
#include "js.h"

#include <string>
int main() {
	std::string url  = inputUrl();
	std::string curl = runCurl(url);

	Level level = CurlToLevel(curl);
	level.print();

	return 0;
}

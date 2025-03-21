#include "level.h"
#include "position.h"

#include <cstdio>
// #include <utility>
#include <vector>


bool _test_getNeighbors();

int  testNumber = 1;
bool beginTests() {
	bool status = true;

	status &= _test_getNeighbors();


	return status;
}

int  main() { return beginTests(); }
bool _test_getNeighbors() {
	printf("%s begin\n", "_test_getNeighbors");
	struct subtest
	{
		Position    pos;
		const char* targets;
		int         expectedResult;
	};
	typedef std::vector<subtest> Subtests;
	struct Test
	{
		Level    level;
		Subtests subtests;
	};
	char* grid = const_cast<char*>((
			const char*)"######"
	                "#....#"
	                "#...+#"
	                "#B.@+#"
	                "#.B.+#"
	                "######");

	Subtests subtests = {
		{{1, 2},  ".", 2},
		{{2, 3}, "B@", 3},
		{{2, 2},  ".", 4},
		{{3, 3},  "+", 1},
		{{4, 3},  "+", 2},
		{{3, 2}, ".+", 3},
		{{1, 1},  "#", 2},
	};

	bool result = true;
	Test test   = {Level(grid, 6, 6), subtests};
	for (int i = 0; i < subtests.size(); i++) {
		printf("%d-%d -> ", testNumber, i);
		if (test.level.getNeighbors(subtests[i].pos, subtests[i].targets)
		    == subtests[i].expectedResult) {
			printf("✅\n");
		} else {
			printf("❌\n");
			result = false;
		}
	}
	printf("%s end\n", "_test_getNeighbors");
	testNumber++;
	return result;
}

#include "level.h"
#include "position.h"

#include <cstdio>
// #include <utility>
#include <cstring>
#include <vector>

namespace Tests {
	bool _test_getNeighbors();
	bool _test_fixEdge();

	int  testNumber = 1;
	bool beginTests() {
		bool status = true;

		status &= _test_getNeighbors();
		status &= _test_fixEdge();


		return status;
	}

	bool _test_getNeighbors() {
		printf("%s:\n", __func__);
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
			if (test.level.getNeighborCnt(subtests[i].pos, subtests[i].targets)
			    == subtests[i].expectedResult) {
				printf("✅\n");
			} else {
				printf("❌\n");
				result = false;
			}
		}
		testNumber++;
		return result;
	}
	bool _test_fixEdge() {
		printf("%s:\n", __func__);
		char* grid = new char[7 * 6 + 1]();
		memset(grid, '3', 7 * 6);
		Level level(grid, 7, 6);
		level.fixEdge();
		const char* expected =
				"#######"
				"#33333#"
				"#33333#"
				"#33333#"
				"#33333#"
				"#######";
		bool result = true;
		if (memcmp(grid, expected, 7 * 6)) { result = false; }
		printf("%d-0 -> %s\n", testNumber, (result ? "✅" : "❌"));
		testNumber++;
		return result;
	}
}  // namespace Tests
int main() { return Tests::beginTests(); }

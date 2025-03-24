#include "level.h"
#include "position.h"

#include <cstdio>
// #include <utility>
#include <cstring>
#include <set>
#include <vector>
#define COLOR_R 31
#define COLOR_G 32
#define COLOR_B 34
int colors[2] = {COLOR_R, COLOR_G};

namespace Tests {
	bool _test_getNeighbors();
	bool _test_getVisible();
	bool _test_fixEdge();
	bool _test_positionOverloads();

	int  testNumber = 1;
	bool beginTests() {
		bool status = true;

		status &= _test_getNeighbors();
		status &= _test_fixEdge();
		status &= _test_positionOverloads();
		status &= _test_getVisible();


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
			bool temp = test.level.getNeighborCnt(subtests[i].pos, subtests[i].targets)
			         == subtests[i].expectedResult;
			printf("\033[%dm%d-%d\033[0m\n", colors[temp], testNumber, i);
			if (!temp) { result = false; }
		}
		testNumber++;
		return result;
	}


	bool vectorsMatch(const std::vector<Position>& a, const std::vector<Position>& b) {
		return std::multiset<Position>(a.begin(), a.end())
		    == std::multiset<Position>(b.begin(), b.end());
	}  // thanks chatgpt
	bool _test_getVisible() {
		printf("%s:\n", __func__);
		bool result = true;
		struct subtest
		{
			Position    pos;
			const char* targets;
			Positions   expectedResult;
		};
		typedef std::vector<subtest> Subtests;
		struct Test
		{
			Level    level;
			Subtests subtests;
		};
		char* grid = const_cast<char*>((
				const char*)"#######"
		                "#.+B..#"
		                "#.B.B.#"
		                "#@@B+.#"
		                "#....+#"
		                "#######");

		Subtests subtests = {
			{{3, 2},  ".",               {}},
			{{4, 1},  "B", {{3, 1}, {4, 2}}},
			{{2, 2},  ".", {{3, 2}, {1, 2}}},
			{{3, 3},  "+",         {{4, 3}}},
			{{4, 3},  "+",               {}},
			{{3, 2}, ".+",               {}},
			{{1, 1},  "#", {{1, 0}, {0, 1}}},
		};

		Test test = {Level(grid, 7, 6), subtests};
		for (int i = 0; i < subtests.size(); i++) {
			bool temp = vectorsMatch(test.level.getVisible(subtests[i].pos, subtests[i].targets),
			                         subtests[i].expectedResult);
			printf("\033[%dm%d-%d\033[0m ", colors[temp], testNumber, i);
			if (!temp) {
				for (Position pos : test.level.getVisible(subtests[i].pos, subtests[i].targets)) {
					printf("(%d, %d), ", pos.x, pos.y);
				}
				printf("\b\b ");
				result = false;
			}
			printf("\n");
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

		// returns 0 when the same
		if (memcmp(grid, expected, 7 * 6)) { result = false; }
		printf("\033[%dm%d-0\033[0m\n", colors[result], testNumber);
		testNumber++;
		return result;
	}
	bool _test_positionOverloads() {
		printf("%s:\n", __func__);
		bool     result = true;
		Position p1{2, 3}, p2{3, 2}, p3{2, 3};
		if (p1 == p2) { result = false; }
		if (p2 == p3) { result = false; }
		if (p1 != p3) { result = false; }
		printf("\033[%dm%d-0\033[0m\n", colors[result], /* (result ? COLOR_G : COLOR_R), */ testNumber);
		bool result2 = true;
		if (p1 > p2) { result = false; }
		if (p1 < p3) { result = false; }
		if (p1 >= p2) { result = false; }
		printf("\033[%dm%d-1\033[0m\n", colors[result2], testNumber);
		testNumber++;
		return result & result2;
	}
}  // namespace Tests
int main() { return Tests::beginTests(); }

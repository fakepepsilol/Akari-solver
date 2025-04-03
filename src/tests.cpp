#include "tests.h"

#include "level.h"
#include "position.h"

#include <cstdio>
#include <cstring>
#include <set>
#include <unordered_map>
#include <vector>
#define COLOR_R 31
#define COLOR_G 32
#define COLOR_B 34
int colors[2] = {COLOR_R, COLOR_G};

namespace Tests {


	// bool _test_getNeighbors();
	// bool _test_getVisible();
	// bool _test_fixEdge();
	// bool _test_positionOverloads();
	// bool _test_getCombinationsForTile();


	int testNumber = 1;

	std::unordered_map<int, int> testNumbers;

	void printTestResult(bool testResult) {
		printf("\033[%dm%d-%d\033[0m\n", colors[testResult], testNumber, testNumbers[testNumber]);
		testNumbers[testNumber]++;
	}


	bool beginTests() {
		bool (*tests[])() = {_test_fixEdge,
		                     _test_getVisible,
		                     _test_getNeighbors,
		                     _test_positionOverloads,
		                     _test_getCombinationsForTile};
		bool status       = true;
		for (bool (*fn)() : tests) {
			status &= fn();
			testNumber++;
		}
		// status &= _test_getNeighbors();
		// status &= _test_fixEdge();
		// status &= _test_positionOverloads();
		// status &= _test_getVisible();
		// status &= _test_getCombinationsForTile();

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

		bool ret  = true;
		Test test = {Level(grid, 6, 6), subtests};
		for (int i = 0; i < subtests.size(); i++) {
			bool result = test.level.getNeighborCnt(subtests[i].pos, subtests[i].targets)
			           == subtests[i].expectedResult;
			printTestResult(result);
			// printf("\033[%dm%d-%d\033[0m\n", colors[temp], testNumber, i);
			if (!result) { ret = false; }
		}
		return ret;
	}


	bool vectorsMatch(const std::vector<Position>& a, const std::vector<Position>& b) {
		return std::multiset<Position>(a.begin(), a.end())
		    == std::multiset<Position>(b.begin(), b.end());
	}  // thanks chatgpt
	bool _test_getVisible() {
		printf("%s:\n", __func__);
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

		bool ret  = true;
		Test test = {Level(grid, 7, 6), subtests};
		for (int i = 0; i < subtests.size(); i++) {
			bool result = vectorsMatch(test.level.getVisible(subtests[i].pos, subtests[i].targets),
			                           subtests[i].expectedResult);
			// printf("\033[%dm%d-%d\033[0m ", colors[result], testNumber, i);
			printTestResult(result);
			if (!result) {
				for (Position pos : test.level.getVisible(subtests[i].pos, subtests[i].targets)) {
					printf("(%d, %d), ", pos.x, pos.y);
				}
				printf("\b\b ");
				ret = false;
				printf("\n");
			}
		}

		return ret;
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
		return result;
	}
	bool _test_positionOverloads() {
		printf("%s:\n", __func__);
		bool     result = true;
		Position p1{2, 3}, p2{3, 2}, p3{2, 3};
		if (p1 == p2) { result = false; }
		if (p2 == p3) { result = false; }
		if (p1 != p3) { result = false; }
		printTestResult(result);
		bool result2 = true;
		if (p1 > p2) { result2 = false; }
		if (p1 < p3) { result2 = false; }
		if (p1 >= p2) { result2 = false; }
		printTestResult(result2);
		return result & result2;
	}
	bool _test_getCombinationsForTile() {
		// printf("%s:\n", __func__);
		bool result = true;
		// const char* grid =
		// 		"#####"
		// 		"#...#"
		// 		"#.2.#"
		// 		"#...#"
		// 		"#####";
		// Level        temp  = Level(const_cast<char*>(grid), 5, 5);
		// Combinations retrn = temp.getCombinationsForTile({2, 2});
		//   Combinations expected = {{{2, 1}, {3, 2}}, {{2, 1}, {2, 3}}, {{2, 1},{1, 2}}, {{3, 2},{1,
		//   2}}, {{2, 3},{1, 2}}}; printTestResult(vectorsMatch(retrn, expected));
		// for (Positions poss : retrn) {
		// 	printf("{");
		// 	for (Position pos : poss) {
		// 		printf("(%d, %d), ", pos.x, pos.y);
		// 	}
		// 	printf("\b\b}, ");
		// }
		// printf("\b\b ");
		//
		return result;
	}
}  // namespace Tests
int main() { return Tests::beginTests(); }

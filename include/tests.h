#pragma once
#include <vector>
namespace Tests {
	typedef std::vector<bool> results;

	bool _test_fixEdge();
	bool _test_getVisible();
	bool _test_getNeighbors();
	bool _test_getNeighborCnt();
	bool _test_positionOverloads();
	bool _test_getCombinationsForTile();
};  // namespace Tests

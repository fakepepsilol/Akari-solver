#pragma once

#include <vector>
struct Position
{
	int x;
	int y;
	// inline bool operator<(const Position& cmp) const { return (x == cmp.x) ? y < cmp.y : x < cmp.x;
	// } inline bool operator==(const Position& cmp) const { return (x == cmp.x) && (y == cmp.y); }
	inline bool operator==(const Position& cmp) const { return (x == cmp.x) && (y == cmp.y); }
	inline bool operator!=(const Position& cmp) const { return !(*this == cmp); }

	inline bool operator<(const Position& cmp) const {
		return (x == cmp.x) ? (y < cmp.y) : (x < cmp.x);
	}
	inline bool operator>(const Position& cmp) const { return cmp < *this; }

	inline bool operator<=(const Position& cmp) const { return !(cmp < *this); }
	inline bool operator>=(const Position& cmp) const { return !(*this < cmp); }
};

typedef std::vector<Position> Positions;  // multiple positions (x, y)


struct ChoicesPerTile
{
	std::vector<Positions> choices;
	Position               tilePosition;
};  // choices for a single tile
typedef std::vector<ChoicesPerTile> Choices;  // all choices / all tiles

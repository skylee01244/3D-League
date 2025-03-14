#include <array>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Headers/Global.h"

gbl::MAP::PathCell get_cell(const sf::Vector2<short>& i_cell, const gbl::MAP::Map<gbl::MAP::PathCell>& i_map)
{
	if (0 <= i_cell.x && 0 <= i_cell.y && i_cell.x < gbl::MAP::COLUMNS && i_cell.y < gbl::MAP::ROWS)
	{
		return i_map[i_cell.x][i_cell.y];
	}

#ifdef DEBUG
	std::cerr << "[Warning] Attempted to access an out-of-bounds cell: ("<< cellPos.x << ", " << cellPos.y << ")\n";
#endif

	return gbl::MAP::PathCell::Invalid;
}
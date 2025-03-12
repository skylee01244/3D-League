#include <array>
#include <chrono>
#include <map>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Headers/Global.h"
#include "Headers/GetCell.h"

//Every cell has a f value(f = g + h)
//g = Distance From start
//h = hypothetical distance from cell to finish

std::vector<sf::Vector2<unsigned short>> get_adjacent_cells(const sf::Vector2<unsigned short>& currentCell, const gbl::MAP::Map<gbl::MAP::PathCell>& map);

float calculate_h_score(const sf::Vector2<unsigned short>& i_cell0, const sf::Vector2<unsigned short>& i_cell1)
{
	const float dx = std::abs(i_cell1.x - i_cell0.x);
	const float dy = std::abs(i_cell1.y - i_cell0.y);

	return std::max(dx, dy) + std::min(dx, dy) * (std::sqrt(2) - 1);
}

void astar_reset(unsigned short& i_path_length, std::map<gbl::Position<>, gbl::Position<>>& i_previous_cell, std::vector<sf::Vector2<unsigned short>>& i_path_vector, gbl::MAP::Map<float>& i_f_scores, gbl::MAP::Map<float>& i_g_scores, gbl::MAP::Map<float>& i_h_scores, const sf::Vector2<unsigned short>& i_finish_position, const sf::Vector2<unsigned short>& i_start_position, gbl::MAP::Map<gbl::MAP::PathCell>& i_map)
{
	i_path_length = 0;
	i_previous_cell.clear();
	i_path_vector.clear();
	i_path_vector.push_back(i_start_position);

	for (unsigned short a = 0; a < gbl::MAP::COLUMNS; a++) {
		for (unsigned short b = 0; b < gbl::MAP::ROWS; b++)
		{
			i_h_scores[a][b] = calculate_h_score(sf::Vector2<unsigned short>(a, b), i_finish_position);

			if (i_map[a][b] != gbl::MAP::PathCell::Wall)
			{
				i_map[a][b] = gbl::MAP::PathCell::Empty;
			}
			if (a == i_start_position.x && b == i_start_position.y)
			{
				i_f_scores[a][b] = i_h_scores[a][b];
				i_g_scores[a][b] = 0;

			}
			else
			{
				i_f_scores[a][b] = std::numeric_limits<float>::max();
				i_g_scores[a][b] = std::numeric_limits<float>::max();
			}
		}
	}
}

void astar_search(unsigned short& i_path_length, std::map<gbl::Position<>, gbl::Position<>>& i_previous_cell, std::vector<sf::Vector2<unsigned short>>& i_path_vector, gbl::MAP::Map<float>& i_f_scores, gbl::MAP::Map<float>& i_g_scores, const gbl::MAP::Map<float>& i_h_scores, sf::Vector2<unsigned short>& i_next_cell, const sf::Vector2<unsigned short>& i_finish_position, const sf::Vector2<unsigned short>& i_start_position, gbl::MAP::Map<gbl::MAP::PathCell>& i_map)
{
	while (!i_path_vector.empty())
	{
		std::vector<sf::Vector2<unsigned short>>::iterator current_iterator = i_path_vector.begin();
		sf::Vector2<unsigned short> currrent_cell;
		for (std::vector<sf::Vector2<unsigned short>>::iterator a = 1 + i_path_vector.begin(); a != i_path_vector.end(); a++)
		{
			if (i_f_scores[a->x][a->y] < i_f_scores[current_iterator->x][current_iterator->y])
			{
				current_iterator = a;
			}
		}

		currrent_cell = *current_iterator;

		if (i_f_scores[currrent_cell.x][currrent_cell.y] == std::numeric_limits<float>::max()) { return; }

		i_path_vector.erase(current_iterator);

		i_map[currrent_cell.x][currrent_cell.y] = gbl::MAP::PathCell::Visited;

		if (currrent_cell == i_finish_position)	{	// reconstruct the path
			gbl::Position<> path_cell(currrent_cell.x, currrent_cell.y);

			do
			{
				i_path_length++;
				i_next_cell.x = path_cell.first;
				i_next_cell.y = path_cell.second;

				path_cell = i_previous_cell.at(path_cell);
			} while (i_start_position.x != path_cell.first || i_start_position.y != path_cell.second);

			return;
		}

		for (const sf::Vector2<unsigned short>& adjacent_cell : get_adjacent_cells(currrent_cell, i_map))
		{
			if (i_map[adjacent_cell.x][adjacent_cell.y] != gbl::MAP::PathCell::Visited)
			{
				float g_score = i_g_scores[currrent_cell.x][currrent_cell.y];

				if (std::abs(adjacent_cell.x - currrent_cell.x) == std::abs(adjacent_cell.y - currrent_cell.y))
				{
					g_score += std::sqrt(2);
				}
				else
				{
					g_score += std::sqrt(1);
				}

				if (g_score < i_g_scores[adjacent_cell.x][adjacent_cell.y])
				{
					i_previous_cell[gbl::Position<>(adjacent_cell.x, adjacent_cell.y)] = gbl::Position<>(currrent_cell.x, currrent_cell.y);

					i_f_scores[adjacent_cell.x][adjacent_cell.y] = g_score + i_h_scores[adjacent_cell.x][adjacent_cell.y];
					i_g_scores[adjacent_cell.x][adjacent_cell.y] = g_score;

					if (i_path_vector.end() == std::find(i_path_vector.begin(), i_path_vector.end(), adjacent_cell))
					{
						i_path_vector.push_back(adjacent_cell);
					}
				}
			}
		}
	}
}

std::vector<sf::Vector2<unsigned short>> get_adjacent_cells(const sf::Vector2<unsigned short>& currentCell, const gbl::MAP::Map<gbl::MAP::PathCell>& map) {

	std::vector<sf::Vector2<unsigned short>> neighbors;

	for (int dy = -1; dy <= 1; ++dy) {
		for (int dx = -1; dx <= 1; ++dx) {
			if (dx == 0 && dy == 0)
				continue;

			const int neighborX = static_cast<int>(currentCell.x) + dx;
			const int neighborY = static_cast<int>(currentCell.y) + dy;
			sf::Vector2<short> neighborPos{ static_cast<short>(neighborX), static_cast<short>(neighborY) };

			const auto neighborCell = get_cell(neighborPos, map);
			if (neighborCell == gbl::MAP::PathCell::Invalid ||
				neighborCell == gbl::MAP::PathCell::Wall) {
				continue;
			}

			if (dx != 0 && dy != 0) {
				sf::Vector2<short> adjacent1{ static_cast<short>(currentCell.x + dx), static_cast<short>(currentCell.y) };
				sf::Vector2<short> adjacent2{ static_cast<short>(currentCell.x), static_cast<short>(currentCell.y + dy) };
				const auto cell1 = get_cell(adjacent1, map);
				const auto cell2 = get_cell(adjacent2, map);

				if (cell1 == gbl::MAP::PathCell::Invalid || cell1 == gbl::MAP::PathCell::Wall ||
					cell2 == gbl::MAP::PathCell::Invalid || cell2 == gbl::MAP::PathCell::Wall) {
					continue;
				}
			}

			neighbors.push_back({ static_cast<unsigned short>(neighborX),
								 static_cast<unsigned short>(neighborY) });
		}
	}
	return neighbors;
}
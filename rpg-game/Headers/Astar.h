#pragma once
#include "Global.h"
#include <SFML/Graphics.hpp>

float calculate_h_score(const sf::Vector2<unsigned short>& i_cell0, const sf::Vector2<unsigned short>& i_cell1);

void astar_reset(unsigned short& i_path_length, std::map<gbl::Position<>, gbl::Position<>>& i_previous_cell, std::vector<sf::Vector2<unsigned short>>& i_path_vector, gbl::MAP::Map<float>& i_f_scores, gbl::MAP::Map<float>& i_g_scores, gbl::MAP::Map<float>& i_h_scores, const sf::Vector2<unsigned short>& i_finish_position, const sf::Vector2<unsigned short>& i_start_position, gbl::MAP::Map<gbl::MAP::PathCell>& i_map);

void astar_search(unsigned short& i_path_length, std::map<gbl::Position<>, gbl::Position<>>& i_previous_cell, std::vector<sf::Vector2<unsigned short>>& i_path_vector, gbl::MAP::Map<float>& i_f_scores, gbl::MAP::Map<float>& i_g_scores, const gbl::MAP::Map<float>& i_h_scores, sf::Vector2<unsigned short>& i_next_cell, const sf::Vector2<unsigned short>& i_finish_position, const sf::Vector2<unsigned short>& i_start_position, gbl::MAP::Map<gbl::MAP::PathCell>& i_map);

std::vector<sf::Vector2<unsigned short>> get_adjacent_cells(const sf::Vector2<unsigned short>& currentCell, const gbl::MAP::Map<gbl::MAP::PathCell>& map);
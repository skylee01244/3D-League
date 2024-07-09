#pragma once
#include "Headers/Global.h"
#include "Player.h"
#include "Enemy.h"

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(Player& i_player, Enemy& i_enemy);
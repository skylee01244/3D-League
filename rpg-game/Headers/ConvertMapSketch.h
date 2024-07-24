#pragma once
#include <vector>
#include "Teemo.h"

gbl::MAP::Map<> convert_map_sketch(std::vector<Decoration>& i_decorations, Player& i_player, Enemy& i_enemy1, Teemo& i_teemo, SpriteManager& i_sprite_manager);
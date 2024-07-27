#pragma once
#include <vector>
#include "Lulu.h"
#include "Teemo.h"

gbl::MAP::Map<> convert_map_sketch(std::vector<Decoration>& i_decorations, Player& i_player, Lulu& i_lulu, Teemo& i_teemo, SpriteManager& i_sprite_manager);
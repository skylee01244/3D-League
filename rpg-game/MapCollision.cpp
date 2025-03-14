#include <array>
#include <cmath>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Headers/Global.h"
#include "Headers/MapCollision.h"

namespace {
    template <typename Predicate>
    bool checkCollision(const float posX, const float posY, const gbl::MAP::Map<>& map, Predicate predicate)
    {
        // Each pair indicates whether to use ceil (true) or floor (false) for the X and Y coordinates.
        constexpr std::array<std::pair<bool, bool>, 4> cornerMethods = { {
            {false, false}, // bottom-left: floor(posX), floor(posY)
            {true,  false}, // bottom-right: ceil(posX), floor(posY)
            {false, true }, // top-left: floor(posX), ceil(posY)
            {true,  true }  // top-right: ceil(posX), ceil(posY)
        } };

        for (const auto& [useCeilX, useCeilY] : cornerMethods)
        {
            const int x = static_cast<int>(useCeilX ? std::ceil(posX) : std::floor(posX));
            const int y = static_cast<int>(useCeilY ? std::ceil(posY) : std::floor(posY));

            if (x >= 0 && y >= 0 && x < gbl::MAP::COLUMNS && y < gbl::MAP::ROWS)
            {
                if (predicate(map[x][y]))
                {
                    return true;
                }
            }
        }
        return false;
    }
}

bool map_collision(const float posX, const float posY, const gbl::MAP::Map<>& map)
{
    return checkCollision(posX, posY, map, [](const auto& cell) {
        return cell != gbl::MAP::Cell::Empty;});
}

bool finish_collision(const float posX, const float posY, const gbl::MAP::Map<>& map)
{
    return checkCollision(posX, posY, map, [](const auto& cell) {
        return cell == gbl::MAP::Cell::FinishWall;});
}

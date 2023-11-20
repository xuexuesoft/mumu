#pragma once

#include "Type.h"

namespace mumu {
namespace game {
namespace object {

/**
 * 游戏物体.
 */
class Object
{
    // 物体的id,在世界中唯一.
    int id;

    // 物体类型
    Type type = Type::Tile;
};

} // namespace object
} // namespace game
} // namespace mumu
#pragma once

#include "Type.h"
#include "box2d/box2d.h"

namespace mumu {
namespace game {
namespace object {

/**
 * 游戏物体.
 */
class Object
{
  public:
    // 物体的id,在世界中唯一.
    int id = -1;

    // 物体类型
    Type type = Type::Tile;

    // box2d里的body
    b2Body* body = nullptr;

    /**
     * @brief 得到世界坐标.
     * @param pos 传入坐标位置.
     */
    void GetWorldPostion(b2Vec2& pos)
    {
        if (body == nullptr) {
            return;
        }
        body->GetWorldPoint(pos);
    }
};

} // namespace object
} // namespace game
} // namespace mumu

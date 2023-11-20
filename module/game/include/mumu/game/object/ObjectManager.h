#pragma once

#include "Object.h"
#include <vector>

namespace mumu {
namespace game {
namespace object {

/**
 * @brief 游戏对象的管理器.
 */
class ObjectManager
{
  public:
    ObjectManager() {}
    ~ObjectManager() {}

    /**
     * @brief 创建一个Tile.
     * @return
     */
    Object* CreateObject(Type type)
    {
        Object* obj = new Object();
        obj->id = _count++;
        obj->type = type;

        listObj.push_back(obj);
        return obj;
    }

  private:
    // 对象计数
    int _count = 0;

    // 记录所有对象的列表
    std::vector<Object*> listObj;
};

} // namespace object
} // namespace game
} // namespace mumu

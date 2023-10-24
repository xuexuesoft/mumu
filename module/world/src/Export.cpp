#include <iostream>
#include "mumu/world/Export.h"
#include "mumu/world/U3DDebugDraw.h"
#include "mumu/world/Log.h"

using namespace xuexue;

namespace mumu {
namespace world {

MUMU_EXPORT PluginError mumu_set_logger(xuexue::LoggerCallback fp)
{
    LogUtil::SetLoggerFunction(fp);
    LogI("设置日志函数完成,尝试输出一条日志!");
    return PluginError::Ok;
}

MUMU_EXPORT PluginError mumu_world_create(GameWorld*& world)
{
    LogI("mumu_world_create():进入函数!");
    world = new GameWorld();
    world->Init();
    return PluginError::Ok;
}

MUMU_EXPORT PluginError mumu_world_step(GameWorld* world)
{
    if (world == nullptr) {
        return PluginError::InvalidHandle;
    }

    world->Step();
    return PluginError::Ok;
}

MUMU_EXPORT PluginError mumu_set_debug_draw_interface(DebugDrawInterface& interface)
{
    U3DDebugDraw::Inst()->SetInterface(interface);
}

} // namespace world
} // namespace mumu
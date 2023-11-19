#include <iostream>
#include "mumu/export/Export.h"
// #include "mumu/world/U3DDebugDraw.h"
#include "mumu/utils/Log.h"

using namespace xuexue;

namespace mumu {
namespace game {

MUMU_EXPORT void muPrintVector(const std::vector<std::string>& strings)
{
    for (std::vector<std::string>::const_iterator it = strings.begin(); it != strings.end(); ++it) {
        std::cout << "mumu/1.0 " << *it << std::endl;
    }
}

MUMU_EXPORT PluginError muSetLogger(xuexue::LoggerCallback fp)
{
    LogUtil::SetLoggerCallback(fp);
    LogI("设置日志函数完成,尝试输出一条日志!");
    return PluginError::Ok;
}

MUMU_EXPORT PluginError muSetLogThr(xuexue::log_level thr)
{
    LogUtil::SetOutputLevelThr(thr);
    return PluginError::Ok;
}

MUMU_EXPORT PluginError muWorldCreate(world::World*& world)
{
    LogI("mumu_world_create():进入函数!");
    world = new world::World();
    world->Init();
    return PluginError::Ok;
}

MUMU_EXPORT PluginError muWorldStep(world::World* world)
{
    if (world == nullptr) {
        return PluginError::InvalidHandle;
    }

    world->Step();
    return PluginError::Ok;
}

// MUMU_EXPORT PluginError mumu_set_debug_draw_interface(DebugDrawInterface& interface)
//{
//     U3DDebugDraw::Inst()->SetInterface(interface);
//     return PluginError::Ok;
// }

MUMU_EXPORT PluginError muAddBodyCircle(world::World* world, float x, float y, float radius)
{
    if (world == nullptr) {
        return PluginError::InvalidHandle;
    }
    //    world->AddBodyCircle(x, y, radius);
    return PluginError::Ok;
}

} // namespace game
} // namespace mumu
#include <iostream>
#include "mumu/export/Export.h"
// #include "mumu/world/U3DDebugDraw.h"
#include "mumu/utils/Log.h"

using namespace xuexue;

namespace mumu {
namespace api {

MUMU_C_EXPORT void PrintVector(const std::vector<std::string>& strings)
{
    for (std::vector<std::string>::const_iterator it = strings.begin(); it != strings.end(); ++it) {
        std::cout << "mumu/1.0 " << *it << std::endl;
    }
}

MUMU_C_EXPORT PluginError SetLogger(xuexue::LoggerCallback fp)
{
    LogUtil::SetLoggerCallback(fp);
    LogI("设置日志函数完成,尝试输出一条日志!");
    return PluginError::Ok;
}

MUMU_C_EXPORT PluginError SetLogThr(xuexue::log_level thr)
{
    LogUtil::SetOutputLevelThr(thr);
    return PluginError::Ok;
}

MUMU_C_EXPORT PluginError WorldCreate(game::world::World*& world)
{
    LogI("mumu_world_create():进入函数!");
    world = new game::world::World();
    world->Init();
    return PluginError::Ok;
}

MUMU_C_EXPORT PluginError WorldStep(game::world::World* world)
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

MUMU_C_EXPORT PluginError AddBodyCircle(game::world::World* world, float x, float y, float radius)
{
    if (world == nullptr) {
        return PluginError::InvalidHandle;
    }
    //    world->AddBodyCircle(x, y, radius);
    return PluginError::Ok;
}

} // namespace api
} // namespace mumu

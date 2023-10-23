#include <iostream>
#include "mumu/world/Export.h"
#include "mumu/world/U3DDebugDraw.h"

MUMU_EXPORT PluginError mumu_set_logger(LoggerCallback fp)
{
    log_set_logger_function(fp);
    return PluginError::Ok;
}

MUMU_EXPORT PluginError mumu_world_create(GameWorld*& world)
{
    world = new GameWorld();
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
    g_debugDraw.SetInterface(interface);
}
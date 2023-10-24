#pragma once

#include <vector>
#include <string>

#include "Error.h"
#include "U3DDebugDraw.h"
#include "GameWorld.h"
#include "Log.h"

#ifdef _WIN32
#    define MUMU_EXPORT extern "C" __declspec(dllexport)
#else
// 在Linux上没有stdcall
#    define MUMU_EXPORT extern "C" __attribute__((visibility("default")))
#endif

namespace mumu {
namespace world {

MUMU_EXPORT void mumu_test();
MUMU_EXPORT void mumu_print_vector(const std::vector<std::string>& strings);

MUMU_EXPORT PluginError mumu_set_logger(xuexue::LoggerCallback fp);
MUMU_EXPORT PluginError mumu_world_create(GameWorld*& world);
MUMU_EXPORT PluginError mumu_world_step(GameWorld* world);

// 设置绘图接口
MUMU_EXPORT PluginError mumu_set_debug_draw_interface(DebugDrawInterface& interface);

} // namespace world
} // namespace mumu

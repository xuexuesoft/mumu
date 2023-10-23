#pragma once

#include <vector>
#include <string>

#include "Error.h"
#include "U3DDebugDraw.h"
#include "GameWorld.h"

#ifdef _WIN32
#    define MUMU_EXPORT __declspec(dllexport)
#else
#    define MUMU_EXPORT
#endif

using namespace mumu::world;

MUMU_EXPORT void mumu_test();
MUMU_EXPORT void mumu_print_vector(const std::vector<std::string>& strings);

MUMU_EXPORT PluginError mumu_set_logger(LoggerCallback* fp);
MUMU_EXPORT PluginError mumu_world_create(GameWorld*& world);
MUMU_EXPORT PluginError mumu_world_step(GameWorld* world);

// 设置绘图接口
MUMU_EXPORT PluginError mumu_set_debug_draw_interface(DebugDrawInterface& interface);

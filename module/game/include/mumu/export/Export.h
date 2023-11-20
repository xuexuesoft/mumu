#pragma once

#include "mumu/export/Error.h"
#include "mumu/game/world/World.h"
#include "mumu/utils/Log.h"

#include <vector>
#include <string>

#ifdef _WIN32
#    define MUMU_C_EXPORT extern "C" __declspec(dllexport)
#else
// 在Linux上没有stdcall
#    define MUMU_C_EXPORT extern "C" __attribute__((visibility("default")))
#endif

namespace mumu {
namespace api {

MUMU_C_EXPORT void Test();
MUMU_C_EXPORT void PrintVector(const std::vector<std::string>& strings);

MUMU_C_EXPORT PluginError SetLogger(xuexue::LoggerCallback fp);
MUMU_C_EXPORT PluginError SetLogThr(xuexue::log_level thr);

// 创建一个世界.
MUMU_C_EXPORT PluginError WorldCreate(game::world::World*& world);

// 执行一步计算.
MUMU_C_EXPORT PluginError WorldStep(game::world::World* world);

// 设置绘图接口
// MUMU_EXPORT PluginError mumu_set_debug_draw_interface(DebugDrawInterface& interface);

// 添加一个body. b2BodyType bodyType, b2Shape::Type shapeType,
MUMU_C_EXPORT PluginError AddBodyCircle(game::world::World* world, float x, float y, float radius);

} // namespace api
} // namespace mumu

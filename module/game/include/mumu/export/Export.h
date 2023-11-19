#pragma once

#include <vector>
#include <string>

#include "Error.h"
#include "mumu/game/world/World.h"
#include "mumu/utils/Log.h"

#ifdef _WIN32
#    define MUMU_EXPORT extern "C" __declspec(dllexport)
#else
// 在Linux上没有stdcall
#    define MUMU_EXPORT extern "C" __attribute__((visibility("default")))
#endif

namespace mumu {
namespace game {

MUMU_EXPORT void muTest();
MUMU_EXPORT void muPrintVector(const std::vector<std::string>& strings);

MUMU_EXPORT PluginError muSetLogger(xuexue::LoggerCallback fp);
MUMU_EXPORT PluginError muSetLogThr(xuexue::log_level thr);

// 创建一个世界.
MUMU_EXPORT PluginError muWorldCreate(world::World*& world);

// 执行一步计算.
MUMU_EXPORT PluginError mumuWorldStep(world::World* world);

// 设置绘图接口
// MUMU_EXPORT PluginError mumu_set_debug_draw_interface(DebugDrawInterface& interface);

// 添加一个body. b2BodyType bodyType, b2Shape::Type shapeType,
MUMU_EXPORT PluginError muAddBodyCircle(world::World* world, float x, float y, float radius);

} // namespace game
} // namespace mumu

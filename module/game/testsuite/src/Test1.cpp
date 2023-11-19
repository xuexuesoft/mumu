//
// Created by dx on 2023/10/23.
//

// #include "Test1.h"
#include "gtest/gtest.h"
#include "mumu/world/Export.h"
#include "mumu/world/GameWorld.h"

#include <thread>
#include <chrono>

using namespace std;
using namespace mumu::world;

GameWorld world;

TEST(world, Init)
{
    world.Init();
    for (int i = 0; i < 10; ++i) {
        world.AddBodyCircle(i, 0);
    }

    for (int i = 0; i < 1000; ++i) {
        world.Step();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}
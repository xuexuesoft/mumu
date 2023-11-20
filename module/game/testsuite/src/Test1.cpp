//
// Created by dx on 2023/10/23.
//

// #include "Test1.h"
#include "gtest/gtest.h"
#include "mumu/export/Export.h"
#include "mumu/testbed/GameWorld.h"

#include "mumu/game/world/World.h"

#include <thread>
#include <chrono>

using namespace std;

TEST(GameWorld, Init)
{
    using namespace mumu::world;
    GameWorld* world = new GameWorld();
    world->Init();
    for (int i = 0; i < 10; ++i) {
        world->AddBodyCircle(i, 0);
    }

    for (int i = 0; i < 50; ++i) {
        world->Step();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    delete world;
}

TEST(World, Init)
{
    using namespace mumu::game::world;
    World world;
    world.Init();
    for (int x = -50; x < 50; x++) {
        for (int y = -50; y < 50; y++) {
            world.AddTile(x, y);
        }
    }

    for (int i = 0; i < 100; ++i) {
        world.Step();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

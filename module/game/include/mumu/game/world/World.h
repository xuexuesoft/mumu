#pragma once

#include "Settings.h"

#include "mumu/game/object/ObjectManager.h"

#include "box2d/box2d.h"

#include <map>
#include <string>
#include <vector>

#ifdef _WIN32
#    define MUMU_CPP_EXPORT __declspec(dllexport)
#else
// 在Linux上没有stdcall
#    define MUMU_CPP_EXPORT __attribute__((visibility("default")))
#endif

namespace mumu {
namespace game {
namespace world {

/**
 * 直接定义一个游戏世界.
 */
class MUMU_CPP_EXPORT World
{
  public:
    // 物理世界
    b2World* _world = nullptr;

    // step的计数
    int32 _stepCount;

    // 这个世界的设置.
    Settings settings;

    // 物体管理器
    object::ObjectManager _objManager;

    /**
     * 初始化.
     */
    void Init()
    {
        // 初始化世界
        b2Vec2 gravity;
        gravity.Set(0.0f, -10.0f);
        _world = new b2World(gravity);

        settings.Reset();
        // m_bomb = NULL;
        // m_textLine = 30;
        // m_textIncrement = 18;
        // m_mouseJoint = NULL;
        // m_pointCount = 0;
        //
        // m_destructionListener.test = this;
        // m_world->SetDestructionListener(&m_destructionListener);
        // m_world->SetContactListener(this);
        // m_world->SetDebugDraw(&g_debugDraw);
    }

    /**
     * @brief 得到所有的物体.这个函数待定.
     */
    void GetAllObject()
    {
        int bodyCount = _world->GetBodyCount();
        _world->GetBodyList();
    }

    /**
     * @brief 向世界中添加一个瓦片.
     * @param x
     * @param y
     * @return
     */
    object::Object* AddTile(float x, float y)
    {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 0.5f); // 使用一半长的x和一半长的y
        b2BodyDef bd;
        bd.type = b2_staticBody;
        bd.position = b2Vec2(x, y);
        object::Object* obj = _objManager.CreateObject(object::Type::Tile);
        bd.userData.pointer = (uintptr_t)obj;

        b2Body* body = _world->CreateBody(&bd);
        body->CreateFixture(&shape, 1.0f); // 1.0f是密度

        // 记录这个body指针
        obj->body = body;
        return obj;
    }

    /**
     * @brief 向世界中添加一个player.
     * @param x
     * @param y
     * @return
     */
    object::Object* AddPlayer(float x, float y)
    {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 0.5f); // 使用一半长的x和一半长的y
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position = b2Vec2(x, y);
        object::Object* obj = _objManager.CreateObject(object::Type::Player);
        bd.userData.pointer = (uintptr_t)obj;

        b2Body* body = _world->CreateBody(&bd);
        body->CreateFixture(&shape, 1.0f); // 1.0f是密度

        // 记录这个body指针
        obj->body = body;
        return obj;
    }

    /**
     * 使用这个类的成员setting执行一步计算.
     */
    void Step()
    {
        float timeStep = settings.m_hertz > 0.0f ? 1.0f / settings.m_hertz : float(0.0f);

        if (settings.m_pause) {
            if (settings.m_singleStep) {
                settings.m_singleStep = 0;
            }
            else {
                timeStep = 0.0f;
            }

            // g_debugDraw.DrawString(5, m_textLine, "****PAUSED****");
            // m_textLine += m_textIncrement;
        }

        _world->SetAllowSleeping(settings.m_enableSleep);
        _world->SetWarmStarting(settings.m_enableWarmStarting);
        _world->SetContinuousPhysics(settings.m_enableContinuous);
        _world->SetSubStepping(settings.m_enableSubStepping);
        _world->Step(timeStep, settings.m_velocityIterations, settings.m_positionIterations);
        if (timeStep > 0.0f) {
            ++_stepCount;
        }
        //        m_pointCount = 0;

        //        uint32 flags = 0;
        //        flags += settings.m_drawShapes * b2Draw::e_shapeBit;
        //        flags += settings.m_drawJoints * b2Draw::e_jointBit;
        //        flags += settings.m_drawAABBs * b2Draw::e_aabbBit;
        //        flags += settings.m_drawCOMs * b2Draw::e_centerOfMassBit;
        //        g_debugDraw.SetFlags(flags);

        //        m_world->DebugDraw();
        //        g_debugDraw.Flush();

        //        if (settings.m_drawStats) {
        //            int32 bodyCount = _world->GetBodyCount();
        //            int32 contactCount = _world->GetContactCount();
        //            int32 jointCount = _world->GetJointCount();
        //            g_debugDraw.DrawString(5, m_textLine, "bodies/contacts/joints = %d/%d/%d", bodyCount, contactCount, jointCount);
        //            m_textLine += m_textIncrement;
        //
        //            int32 proxyCount = _world->GetProxyCount();
        //            int32 height = _world->GetTreeHeight();
        //            int32 balance = _world->GetTreeBalance();
        //            float quality = _world->GetTreeQuality();
        //            g_debugDraw.DrawString(5, m_textLine, "proxies/height/balance/quality = %d/%d/%d/%g", proxyCount, height, balance, quality);
        //            m_textLine += m_textIncrement;
    }
};

} // namespace world
} // namespace game
} // namespace mumu

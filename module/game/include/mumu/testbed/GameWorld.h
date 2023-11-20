#pragma once

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
namespace world {

struct ContactPoint
{
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    b2Vec2 normal;
    b2Vec2 position;
    b2PointState state;
    float normalImpulse;
    float tangentImpulse;
    float separation;
};

const int32 k_maxContactPoints = 2048;

class MUMU_CPP_EXPORT GameWorld : public b2ContactListener
{
  public:
    struct Settings
    {
        void Reset()
        {
            //            m_testIndex = 0;
            //            m_windowWidth = 1600;
            //            m_windowHeight = 900;
            m_hertz = 60.0f;
            m_velocityIterations = 8;
            m_positionIterations = 3;
            m_drawShapes = true;
            m_drawJoints = true;
            m_drawAABBs = false;

            m_drawContactPoints = false;
            m_drawContactNormals = false;
            m_drawContactImpulse = false;
            m_drawFrictionImpulse = false;

            m_drawCOMs = false;

            m_drawStats = false;
            m_drawProfile = false;

            m_enableWarmStarting = true;
            m_enableContinuous = true;
            m_enableSubStepping = false;
            m_enableSleep = true;
            m_pause = false;
            m_singleStep = false;
        }

        //        int m_testIndex;
        //        int m_windowWidth;
        //        int m_windowHeight;
        float m_hertz;
        int m_velocityIterations;
        int m_positionIterations;
        bool m_drawShapes;
        bool m_drawJoints;
        bool m_drawAABBs;

        bool m_drawContactPoints;
        bool m_drawContactNormals;
        bool m_drawContactImpulse;
        bool m_drawFrictionImpulse;

        bool m_drawCOMs;

        // 控制是否绘制状态等信息
        bool m_drawStats;
        bool m_drawProfile;

        bool m_enableWarmStarting;
        bool m_enableContinuous;
        bool m_enableSubStepping;
        bool m_enableSleep;
        bool m_pause;
        bool m_singleStep;
    };

    void Init();

    /**
     * 添加一个圆形的动态Body
     * @param x position.x
     * @param y position.y
     * @param radius 半径
     */
    void AddBodyCircle(float x, float y, float radius = 0.5f);

    void AddBodyBox(float hx, float hy, float x, float y);

    /**
     * 使用自己的默认设置执行一步.
     */
    virtual void Step()
    {
        Step(_settings);
    }

    virtual void Step(Settings& settings);

    // Let derived tests know that a joint was destroyed.
    virtual void JointDestroyed(b2Joint* joint)
    {
        B2_NOT_USED(joint);
    }

    // Callbacks for derived classes.
    virtual void BeginContact(b2Contact* contact) override
    {
        B2_NOT_USED(contact);
    }

    virtual void EndContact(b2Contact* contact) override
    {
        B2_NOT_USED(contact);
    }

    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
    {
        B2_NOT_USED(contact);
        B2_NOT_USED(impulse);
    }

  protected:
    b2World* m_world;

    b2Profile m_maxProfile;
    b2Profile m_totalProfile;
    int32 m_stepCount;

    // 这个是什么用
    int32 m_pointCount;

    // 用来在画文本的时候递增位置
    int32 m_textLine;
    int32 m_textIncrement;

    // 用来记录ContactPoint的数组
    ContactPoint m_points[k_maxContactPoints];

    // 一个id对应的表
    std::map<int, b2Body*> _mBodys;

    int _curID = 0;

    // 默认设置
    Settings _settings;
};

} // namespace world
} // namespace mumu

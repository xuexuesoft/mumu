#pragma once

namespace mumu {
namespace game {
namespace world {

/**
 * 一个世界里物理属性设置.
 */
class Settings
{
  public:

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

} // namespace world
} // namespace game
} // namespace mumu
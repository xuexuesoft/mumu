//
// Created by dx on 2023/10/23.
//

#include "mumu/world/GameWorld.h"
#include "mumu/world/U3DDebugDraw.h"

#define LogI printf

namespace mumu {
namespace world {

extern U3DDebugDraw g_debugDraw;

void GameWorld::Init()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    m_world = new b2World(gravity);

    memset(&m_maxProfile, 0, sizeof(b2Profile));
    memset(&m_totalProfile, 0, sizeof(b2Profile));

    _settings.Reset();
}

void GameWorld::AddBodyCircle(float radius, float x, float y)
{
    b2CircleShape shape;
    shape.m_p.SetZero();
    shape.m_radius = 0.1f;

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position = b2Vec2(x, y);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&shape, 0.01f);

    // 记录id
    _mBodys[_curID++] = body;
}

void GameWorld::AddBodyBox(float hx, float hy, float x, float y)
{
}

void GameWorld::Step(GameWorld::Settings& settings)
{
    LogD("GameWorld.Step():进入函数...");

    float timeStep = settings.m_hertz > 0.0f ? 1.0f / settings.m_hertz : float(0.0f);

    if (settings.m_pause) {
        if (settings.m_singleStep) {
            settings.m_singleStep = 0;
        }
        else {
            timeStep = 0.0f;
        }

        g_debugDraw.DrawString(5, m_textLine, "****PAUSED****");
        m_textLine += m_textIncrement;
    }

    uint32 flags = 0;
    flags += settings.m_drawShapes * b2Draw::e_shapeBit;
    flags += settings.m_drawJoints * b2Draw::e_jointBit;
    flags += settings.m_drawAABBs * b2Draw::e_aabbBit;
    flags += settings.m_drawCOMs * b2Draw::e_centerOfMassBit;
    g_debugDraw.SetFlags(flags);

    m_world->SetAllowSleeping(settings.m_enableSleep);
    m_world->SetWarmStarting(settings.m_enableWarmStarting);
    m_world->SetContinuousPhysics(settings.m_enableContinuous);
    m_world->SetSubStepping(settings.m_enableSubStepping);

    m_pointCount = 0;

    m_world->Step(timeStep, settings.m_velocityIterations, settings.m_positionIterations);

    m_world->DebugDraw();
    g_debugDraw.Flush();

    if (timeStep > 0.0f) {
        ++m_stepCount;
    }

    m_world->SetAllowSleeping(settings.m_enableSleep);
    m_world->SetWarmStarting(settings.m_enableWarmStarting);
    m_world->SetContinuousPhysics(settings.m_enableContinuous);
    m_world->SetSubStepping(settings.m_enableSubStepping);

    m_pointCount = 0;

    m_world->Step(timeStep, settings.m_velocityIterations, settings.m_positionIterations);

    m_world->DebugDraw();
    g_debugDraw.Flush();

    if (timeStep > 0.0f) {
        ++m_stepCount;
    }

    if (settings.m_drawStats) {
        int32 bodyCount = m_world->GetBodyCount();
        int32 contactCount = m_world->GetContactCount();
        int32 jointCount = m_world->GetJointCount();
        g_debugDraw.DrawString(5, m_textLine, "bodies/contacts/joints = %d/%d/%d", bodyCount, contactCount, jointCount);
        m_textLine += m_textIncrement;

        int32 proxyCount = m_world->GetProxyCount();
        int32 height = m_world->GetTreeHeight();
        int32 balance = m_world->GetTreeBalance();
        float quality = m_world->GetTreeQuality();
        g_debugDraw.DrawString(5, m_textLine, "proxies/height/balance/quality = %d/%d/%d/%g", proxyCount, height, balance, quality);
        m_textLine += m_textIncrement;
    }

    // Track maximum profile times
    {
        const b2Profile& p = m_world->GetProfile();
        m_maxProfile.step = b2Max(m_maxProfile.step, p.step);
        m_maxProfile.collide = b2Max(m_maxProfile.collide, p.collide);
        m_maxProfile.solve = b2Max(m_maxProfile.solve, p.solve);
        m_maxProfile.solveInit = b2Max(m_maxProfile.solveInit, p.solveInit);
        m_maxProfile.solveVelocity = b2Max(m_maxProfile.solveVelocity, p.solveVelocity);
        m_maxProfile.solvePosition = b2Max(m_maxProfile.solvePosition, p.solvePosition);
        m_maxProfile.solveTOI = b2Max(m_maxProfile.solveTOI, p.solveTOI);
        m_maxProfile.broadphase = b2Max(m_maxProfile.broadphase, p.broadphase);

        m_totalProfile.step += p.step;
        m_totalProfile.collide += p.collide;
        m_totalProfile.solve += p.solve;
        m_totalProfile.solveInit += p.solveInit;
        m_totalProfile.solveVelocity += p.solveVelocity;
        m_totalProfile.solvePosition += p.solvePosition;
        m_totalProfile.solveTOI += p.solveTOI;
        m_totalProfile.broadphase += p.broadphase;
    }

    if (settings.m_drawProfile) {
        const b2Profile& p = m_world->GetProfile();

        b2Profile aveProfile;
        memset(&aveProfile, 0, sizeof(b2Profile));
        if (m_stepCount > 0) {
            float scale = 1.0f / m_stepCount;
            aveProfile.step = scale * m_totalProfile.step;
            aveProfile.collide = scale * m_totalProfile.collide;
            aveProfile.solve = scale * m_totalProfile.solve;
            aveProfile.solveInit = scale * m_totalProfile.solveInit;
            aveProfile.solveVelocity = scale * m_totalProfile.solveVelocity;
            aveProfile.solvePosition = scale * m_totalProfile.solvePosition;
            aveProfile.solveTOI = scale * m_totalProfile.solveTOI;
            aveProfile.broadphase = scale * m_totalProfile.broadphase;
        }

        g_debugDraw.DrawString(5, m_textLine, "step [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.step, aveProfile.step, m_maxProfile.step);
        m_textLine += m_textIncrement;
        g_debugDraw.DrawString(5, m_textLine, "collide [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.collide, aveProfile.collide, m_maxProfile.collide);
        m_textLine += m_textIncrement;
        g_debugDraw.DrawString(5, m_textLine, "solve [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.solve, aveProfile.solve, m_maxProfile.solve);
        m_textLine += m_textIncrement;
        g_debugDraw.DrawString(5, m_textLine, "solve init [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.solveInit, aveProfile.solveInit, m_maxProfile.solveInit);
        m_textLine += m_textIncrement;
        g_debugDraw.DrawString(5, m_textLine, "solve velocity [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.solveVelocity, aveProfile.solveVelocity, m_maxProfile.solveVelocity);
        m_textLine += m_textIncrement;
        g_debugDraw.DrawString(5, m_textLine, "solve position [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.solvePosition, aveProfile.solvePosition, m_maxProfile.solvePosition);
        m_textLine += m_textIncrement;
        g_debugDraw.DrawString(5, m_textLine, "solveTOI [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.solveTOI, aveProfile.solveTOI, m_maxProfile.solveTOI);
        m_textLine += m_textIncrement;
        g_debugDraw.DrawString(5, m_textLine, "broad-phase [ave] (max) = %5.2f [%6.2f] (%6.2f)", p.broadphase, aveProfile.broadphase, m_maxProfile.broadphase);
        m_textLine += m_textIncrement;
    }

    //    if (m_bombSpawning)
    //    {
    //        b2Color c;
    //        c.Set(0.0f, 0.0f, 1.0f);
    //        g_debugDraw.DrawPoint(m_bombSpawnPoint, 4.0f, c);
    //
    //        c.Set(0.8f, 0.8f, 0.8f);
    //        g_debugDraw.DrawSegment(m_mouseWorld, m_bombSpawnPoint, c);
    //    }

    if (settings.m_drawContactPoints) {
        const float k_impulseScale = 0.1f;
        const float k_axisScale = 0.3f;

        for (int32 i = 0; i < m_pointCount; ++i) {
            ContactPoint* point = m_points + i;

            if (point->state == b2_addState) {
                // Add
                g_debugDraw.DrawPoint(point->position, 10.0f, b2Color(0.3f, 0.95f, 0.3f));
            }
            else if (point->state == b2_persistState) {
                // Persist
                g_debugDraw.DrawPoint(point->position, 5.0f, b2Color(0.3f, 0.3f, 0.95f));
            }

            if (settings.m_drawContactNormals == 1) {
                b2Vec2 p1 = point->position;
                b2Vec2 p2 = p1 + k_axisScale * point->normal;
                g_debugDraw.DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.9f));
            }
            else if (settings.m_drawContactImpulse == 1) {
                b2Vec2 p1 = point->position;
                b2Vec2 p2 = p1 + k_impulseScale * point->normalImpulse * point->normal;
                g_debugDraw.DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.3f));
            }

            if (settings.m_drawFrictionImpulse == 1) {
                b2Vec2 tangent = b2Cross(point->normal, 1.0f);
                b2Vec2 p1 = point->position;
                b2Vec2 p2 = p1 + k_impulseScale * point->tangentImpulse * tangent;
                g_debugDraw.DrawSegment(p1, p2, b2Color(0.9f, 0.9f, 0.3f));
            }
        }
    }
}
void GameWorld::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    const b2Manifold* manifold = contact->GetManifold();

    if (manifold->pointCount == 0) {
        return;
    }

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
    b2GetPointStates(state1, state2, oldManifold, manifold);

    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    for (int32 i = 0; i < manifold->pointCount && m_pointCount < k_maxContactPoints; ++i) {
        //		ContactPoint* cp = m_points + m_pointCount;
        ContactPoint* cp = &m_points[m_pointCount];
        cp->fixtureA = fixtureA;
        cp->fixtureB = fixtureB;
        cp->position = worldManifold.points[i];
        cp->normal = worldManifold.normal;
        cp->state = state2[i];
        cp->normalImpulse = manifold->points[i].normalImpulse;
        cp->tangentImpulse = manifold->points[i].tangentImpulse;
        cp->separation = worldManifold.separations[i];
        ++m_pointCount;
    }
}

} // namespace world
} // namespace mumu
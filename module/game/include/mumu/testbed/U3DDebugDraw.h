#pragma once

#ifndef MUMU_U3DDEBUGDRAW_H
#    define MUMU_U3DDEBUGDRAW_H

#    include "box2d/box2d.h"

#    ifdef _WIN32
#        define MUMU_CPP_EXPORT __declspec(dllexport)
#    else
// 在Linux上没有stdcall
#        define MUMU_CPP_EXPORT __attribute__((visibility("default")))
#    endif

namespace mumu {
namespace world {

typedef void (*DrawPolygonCallback)(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
typedef void (*DrawSolidPolygonCallback)(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
typedef void (*DrawCircleCallback)(const b2Vec2& center, float radius, const b2Color& color);
typedef void (*DrawSolidCircleCallback)(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);
typedef void (*DrawSegmentCallback)(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
typedef void (*DrawTransformCallback)(const b2Transform& xf);
typedef void (*DrawPointCallback)(const b2Vec2& p, float size, const b2Color& color);
typedef void (*DrawStringCallback)(int x, int y, const char* string);
typedef void (*DrawAABBCallback)(b2AABB* aabb, const b2Color& color);

/**
 * 调试绘图接口
 */
struct DebugDrawInterface
{
    DrawPolygonCallback OnDrawPolygon = nullptr;
    DrawSolidPolygonCallback OnDrawSolidPolygon = nullptr;
    DrawCircleCallback OnDrawCircle = nullptr;
    DrawSolidCircleCallback OnDrawSolidCircle = nullptr;
    DrawSegmentCallback OnDrawSegment = nullptr;
    DrawTransformCallback OnDrawTransform = nullptr;
    DrawPointCallback OnDrawPoint = nullptr;
    DrawStringCallback OnDrawString = nullptr;
    DrawAABBCallback OnDrawAABB = nullptr;
};

/**
 * u3d调试绘图接口.
 */
class MUMU_CPP_EXPORT U3DDebugDraw : public b2Draw
{
  public:
    U3DDebugDraw();
    virtual ~U3DDebugDraw();

    static U3DDebugDraw* Inst()
    {
        return m_pInstance;
    }

    void Create();
    void Destroy();

    void SetInterface(DebugDrawInterface anInterface);

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;

    // 绘制实心圆
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;

    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

    void DrawTransform(const b2Transform& xf) override;

    void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;

    void DrawString(int x, int y, const char* string, ...);

    void DrawString(const b2Vec2& p, const char* string, ...);

    void DrawAABB(b2AABB* aabb, const b2Color& color);

    void Flush();

    bool m_showUI;
    //    GLRenderPoints* m_points;
    //    GLRenderLines* m_lines;
    //    GLRenderTriangles* m_triangles;

  private:
    static U3DDebugDraw* m_pInstance;

    DebugDrawInterface _interface;
};

} // namespace world
} // namespace mumu

#endif // MUMU_U3DDEBUGDRAW_H

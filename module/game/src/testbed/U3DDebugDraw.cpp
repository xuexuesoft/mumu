//
// Created by dx on 2023/10/23.
//

#include "mumu/testbed/U3DDebugDraw.h"
// #include "mumu/world/Export.h"
#include "mumu/utils/Log.h"
#include <vector>

namespace mumu {
namespace world {

U3DDebugDraw *U3DDebugDraw::m_pInstance = new U3DDebugDraw();

U3DDebugDraw::U3DDebugDraw()
{
}

U3DDebugDraw::~U3DDebugDraw()
{
}

void U3DDebugDraw::Create()
{
}

void U3DDebugDraw::Destroy()
{
}

void U3DDebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    LogD("U3DDebugDraw.DrawPolygon():进入函数...");
    if (_interface.OnDrawPolygon) {
        _interface.OnDrawPolygon(vertices, vertexCount, color);
    }
}

void U3DDebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    LogD("U3DDebugDraw.DrawSolidPolygon():进入函数...");
    if (_interface.OnDrawSolidPolygon) {
        _interface.OnDrawSolidPolygon(vertices, vertexCount, color);
    }
}

void U3DDebugDraw::DrawCircle(const b2Vec2 &center, float radius, const b2Color &color)
{
    LogD("U3DDebugDraw.DrawCircle():进入函数...");
    if (_interface.OnDrawCircle) {
        _interface.OnDrawCircle(center, radius, color);
    }
}

void U3DDebugDraw::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color)
{
    LogD("U3DDebugDraw.DrawSolidCircle():进入函数...");
    if (_interface.OnDrawSolidCircle) {
        _interface.OnDrawSolidCircle(center, radius, axis, color);
    }
}

void U3DDebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
{
    LogD("U3DDebugDraw.DrawSegment():进入函数...");
    if (_interface.OnDrawSegment) {
        _interface.OnDrawSegment(p1, p2, color);
    }
}

void U3DDebugDraw::DrawTransform(const b2Transform &xf)
{
    LogD("U3DDebugDraw.DrawTransform():进入函数...");
    if (_interface.OnDrawTransform) {
        _interface.OnDrawTransform(xf);
    }
}

void U3DDebugDraw::DrawPoint(const b2Vec2 &p, float size, const b2Color &color)
{
    LogD("U3DDebugDraw.DrawPoint():进入函数...");
    if (_interface.OnDrawPoint) {
        _interface.OnDrawPoint(p, size, color);
    }
}

void U3DDebugDraw::DrawString(int x, int y, const char *strFormat, ...)
{
    LogD("U3DDebugDraw.DrawString():进入函数...");
    if (_interface.OnDrawString) {

        std::vector<char> buf(128, '\0');
        int ret = 0;
        va_list arg_ptr;
        va_start(arg_ptr, strFormat);
        // 最多执行4次增加buff长度
        for (size_t count = 0; count < 4; count++) {
            // vsnprintf的返回是不包含\0的预留位置的
            ret = vsnprintf(buf.data(), buf.size(), strFormat, arg_ptr);
            if (ret <= 0) {
                break; // 编码失败
            }
            else if (ret >= buf.size()) {
                // buff长度不够
                buf.resize((size_t)ret * 4, '\0');
                // 在GCC平台需要重新生成一下arg_ptr
                va_end(arg_ptr);
                va_start(arg_ptr, strFormat);
            }
            else {
                // 编码成功
                break;
            }
        }
        va_end(arg_ptr);
        _interface.OnDrawString(x, y, buf.data());
    }
}

void U3DDebugDraw::DrawString(const b2Vec2 &p, const char *strFormat, ...)
{
    LogD("U3DDebugDraw.DrawString():进入函数...");
    if (_interface.OnDrawString) {
        std::vector<char> buf(128, '\0');
        int ret = 0;
        va_list arg_ptr;
        va_start(arg_ptr, strFormat);
        // 最多执行4次增加buff长度
        for (size_t count = 0; count < 4; count++) {
            // vsnprintf的返回是不包含\0的预留位置的
            ret = vsnprintf(buf.data(), buf.size(), strFormat, arg_ptr);
            if (ret <= 0) {
                break; // 编码失败
            }
            else if (ret >= buf.size()) {
                // buff长度不够
                buf.resize((size_t)ret * 4, '\0');
                // 在GCC平台需要重新生成一下arg_ptr
                va_end(arg_ptr);
                va_start(arg_ptr, strFormat);
            }
            else {
                // 编码成功
                break;
            }
        }
        va_end(arg_ptr);
        _interface.OnDrawString(p.x, p.y, buf.data());
    }
}

void U3DDebugDraw::DrawAABB(b2AABB *aabb, const b2Color &color)
{
    LogD("U3DDebugDraw.DrawAABB():进入函数...");
    if (_interface.OnDrawAABB) {
        _interface.OnDrawAABB(aabb, color);
    }
}

void U3DDebugDraw::Flush()
{
    LogD("U3DDebugDraw.Flush():进入函数...");
}

void U3DDebugDraw::SetInterface(DebugDrawInterface anInterface)
{
    LogD("U3DDebugDraw.SetInterface():设置了传入的接口");
    this->_interface = anInterface;
}

} // namespace world
} // namespace mumu
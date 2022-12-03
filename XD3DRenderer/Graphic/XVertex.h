#pragma once

//#include "D3D/SimpleMath.h"
#include "Color.h"
#include "XMath.h"

struct XVertex
{
    XVertex() {}
    XVertex(
        const XVector3& p,
        const XVector3& n,
        const XVector3& t,
        const XVector2& uv) :
        Position(p),
        Normal(n),
        TangentU(t),
        TexC(uv) {}
    XVertex(
        float px, float py, float pz,
        float nx, float ny, float nz,
        float tx, float ty, float tz,
        float u, float v) :
        Position(px, py, pz),
        Normal(nx, ny, nz),
        TangentU(tx, ty, tz),
        TexC(u, v) {}

    XVector3 Position;
    XVector3 Normal;
    XVector3 TangentU;
    XVector2 TexC;
};

struct TPrimitiveVertex
{
    TPrimitiveVertex() {}
    TPrimitiveVertex(
        const XVector3& p,
        const XColor& c) :
        Position(p),
        Color(c) {}

    TPrimitiveVertex(
        float px, float py, float pz,
        float cr, float cg, float cb, float ca) :
        Position(px, py, pz),
        Color(cr, cg, cb, ca) {}

    XVector3 Position;
    XColor Color;
};

struct TSpriteVertex
{
    TSpriteVertex() {}
    TSpriteVertex(
        const XVector3& p,
        const XVector2& uv) :
        Position(p),
        TexC(uv) {}

    XVector3 Position;
    XVector2 TexC;
};
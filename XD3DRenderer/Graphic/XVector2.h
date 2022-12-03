// Modified version of DirectXTK12's source file

//-------------------------------------------------------------------------------------
// SimpleMath.h -- Simplified C++ Math wrapper for DirectXMath
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
// http://go.microsoft.com/fwlink/?LinkID=615561
//-------------------------------------------------------------------------------------

#pragma once

#include <DirectXMath.h>

// 2D vector
struct XVector2 : public DirectX::XMFLOAT2
{
	XVector2() noexcept : XMFLOAT2(0.f, 0.f) {}
	constexpr explicit XVector2(float ix) noexcept : XMFLOAT2(ix, ix) {}
	constexpr XVector2(float ix, float iy) noexcept : XMFLOAT2(ix, iy) {}
	explicit XVector2(_In_reads_(2) const float* pArray) noexcept : XMFLOAT2(pArray) {}
	XVector2(DirectX::FXMVECTOR V) noexcept { XMStoreFloat2(this, V); }
	XVector2(const XMFLOAT2& V) noexcept { this->x = V.x; this->y = V.y; }
	explicit XVector2(const DirectX::XMVECTORF32& F) noexcept { this->x = F.f[0]; this->y = F.f[1]; }

	XVector2(const XVector2&) = default;
	XVector2& operator=(const XVector2&) = default;

	XVector2(XVector2&&) = default;
	XVector2& operator=(XVector2&&) = default;

	operator DirectX::XMVECTOR() const noexcept { return XMLoadFloat2(this); }

	// Comparison operators
	bool operator == (const XVector2& V) const noexcept;
	bool operator != (const XVector2& V) const noexcept;

	// Assignment operators
	XVector2& operator= (const DirectX::XMVECTORF32& F) noexcept { x = F.f[0]; y = F.f[1]; return *this; }
	XVector2& operator+= (const XVector2& V) noexcept;
	XVector2& operator-= (const XVector2& V) noexcept;
	XVector2& operator*= (const XVector2& V) noexcept;
	XVector2& operator*= (float S) noexcept;
	XVector2& operator/= (float S) noexcept;

	// Unary operators
	XVector2 operator+ () const noexcept { return *this; }
	XVector2 operator- () const noexcept { return XVector2(-x, -y); }

	// Vector operations
	bool InBounds(const XVector2& Bounds) const noexcept;

	float Length() const noexcept;
	float LengthSquared() const noexcept;

	float Dot(const XVector2& V) const noexcept;
	void Cross(const XVector2& V, XVector2& result) const noexcept;
	XVector2 Cross(const XVector2& V) const noexcept;

	void Normalize() noexcept;
	void Normalize(XVector2& result) const noexcept;

	void Clamp(const XVector2& vmin, const XVector2& vmax) noexcept;
	void Clamp(const XVector2& vmin, const XVector2& vmax, XVector2& result) const noexcept;

	// Static functions
	static float Distance(const XVector2& v1, const XVector2& v2) noexcept;
	static float DistanceSquared(const XVector2& v1, const XVector2& v2) noexcept;

	static void Min(const XVector2& v1, const XVector2& v2, XVector2& result) noexcept;
	static XVector2 Min(const XVector2& v1, const XVector2& v2) noexcept;

	static void Max(const XVector2& v1, const XVector2& v2, XVector2& result) noexcept;
	static XVector2 Max(const XVector2& v1, const XVector2& v2) noexcept;

	static void Lerp(const XVector2& v1, const XVector2& v2, float t, XVector2& result) noexcept;
	static XVector2 Lerp(const XVector2& v1, const XVector2& v2, float t) noexcept;

	static void SmoothStep(const XVector2& v1, const XVector2& v2, float t, XVector2& result) noexcept;
	static XVector2 SmoothStep(const XVector2& v1, const XVector2& v2, float t) noexcept;

	static void Barycentric(const XVector2& v1, const XVector2& v2, const XVector2& v3, float f, float g, XVector2& result) noexcept;
	static XVector2 Barycentric(const XVector2& v1, const XVector2& v2, const XVector2& v3, float f, float g) noexcept;

	static void CatmullRom(const XVector2& v1, const XVector2& v2, const XVector2& v3, const XVector2& v4, float t, XVector2& result) noexcept;
	static XVector2 CatmullRom(const XVector2& v1, const XVector2& v2, const XVector2& v3, const XVector2& v4, float t) noexcept;

	static void Hermite(const XVector2& v1, const XVector2& t1, const XVector2& v2, const XVector2& t2, float t, XVector2& result) noexcept;
	static XVector2 Hermite(const XVector2& v1, const XVector2& t1, const XVector2& v2, const XVector2& t2, float t) noexcept;

	static void Reflect(const XVector2& ivec, const XVector2& nvec, XVector2& result) noexcept;
	static XVector2 Reflect(const XVector2& ivec, const XVector2& nvec) noexcept;

	static void Refract(const XVector2& ivec, const XVector2& nvec, float refractionIndex, XVector2& result) noexcept;
	static XVector2 Refract(const XVector2& ivec, const XVector2& nvec, float refractionIndex) noexcept;

	// Constants
	static const XVector2 Zero;
	static const XVector2 One;
	static const XVector2 UnitX;
	static const XVector2 UnitY;
};

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XVector2::operator == (const XVector2& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	return XMVector2Equal(v1, v2);
}

inline bool XVector2::operator != (const XVector2& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	return XMVector2NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline XVector2& XVector2::operator+= (const XVector2& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat2(this, X);
	return *this;
}

inline XVector2& XVector2::operator-= (const XVector2& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat2(this, X);
	return *this;
}

inline XVector2& XVector2::operator*= (const XVector2& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat2(this, X);
	return *this;
}

inline XVector2& XVector2::operator*= (float S) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat2(this, X);
	return *this;
}

inline XVector2& XVector2::operator/= (float S) noexcept
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat2(this, X);
	return *this;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline XVector2 operator+ (const XVector2& V1, const XVector2& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XVector2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XVector2 operator- (const XVector2& V1, const XVector2& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XVector2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XVector2 operator* (const XVector2& V1, const XVector2& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XVector2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XVector2 operator* (const XVector2& V, float S) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XVector2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XVector2 operator/ (const XVector2& V1, const XVector2& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XVector2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XVector2 operator/ (const XVector2& V, float S) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XVector2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XVector2 operator* (float S, const XVector2& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XVector2 R;
	XMStoreFloat2(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool XVector2::InBounds(const XVector2& Bounds) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&Bounds);
	return XMVector2InBounds(v1, v2);
}

inline float XVector2::Length() const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR X = XMVector2Length(v1);
	return XMVectorGetX(X);
}

inline float XVector2::LengthSquared() const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR X = XMVector2LengthSq(v1);
	return XMVectorGetX(X);
}

inline float XVector2::Dot(const XVector2& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2Dot(v1, v2);
	return XMVectorGetX(X);
}

inline void XVector2::Cross(const XVector2& V, XVector2& result) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR R = XMVector2Cross(v1, v2);
	XMStoreFloat2(&result, R);
}

inline XVector2 XVector2::Cross(const XVector2& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR R = XMVector2Cross(v1, v2);

	XVector2 result;
	XMStoreFloat2(&result, R);
	return result;
}

inline void XVector2::Normalize() noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR X = XMVector2Normalize(v1);
	XMStoreFloat2(this, X);
}

inline void XVector2::Normalize(XVector2& result) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR X = XMVector2Normalize(v1);
	XMStoreFloat2(&result, X);
}

inline void XVector2::Clamp(const XVector2& vmin, const XVector2& vmax) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&vmin);
	XMVECTOR v3 = XMLoadFloat2(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat2(this, X);
}

inline void XVector2::Clamp(const XVector2& vmin, const XVector2& vmax, XVector2& result) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&vmin);
	XMVECTOR v3 = XMLoadFloat2(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat2(&result, X);
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float XVector2::Distance(const XVector2& v1, const XVector2& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR V = XMVectorSubtract(x2, x1);
	XMVECTOR X = XMVector2Length(V);
	return XMVectorGetX(X);
}

inline float XVector2::DistanceSquared(const XVector2& v1, const XVector2& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR V = XMVectorSubtract(x2, x1);
	XMVECTOR X = XMVector2LengthSq(V);
	return XMVectorGetX(X);
}

inline void XVector2::Min(const XVector2& v1, const XVector2& v2, XVector2& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR X = XMVectorMin(x1, x2);
	XMStoreFloat2(&result, X);
}

inline XVector2 XVector2::Min(const XVector2& v1, const XVector2& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR X = XMVectorMin(x1, x2);

	XVector2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XVector2::Max(const XVector2& v1, const XVector2& v2, XVector2& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR X = XMVectorMax(x1, x2);
	XMStoreFloat2(&result, X);
}

inline XVector2 XVector2::Max(const XVector2& v1, const XVector2& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR X = XMVectorMax(x1, x2);

	XVector2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XVector2::Lerp(const XVector2& v1, const XVector2& v2, float t, XVector2& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);
	XMStoreFloat2(&result, X);
}

inline XVector2 XVector2::Lerp(const XVector2& v1, const XVector2& v2, float t) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);

	XVector2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XVector2::SmoothStep(const XVector2& v1, const XVector2& v2, float t, XVector2& result) noexcept
{
	using namespace DirectX;
	t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
	t = t * t * (3.f - 2.f * t);
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);
	XMStoreFloat2(&result, X);
}

inline XVector2 XVector2::SmoothStep(const XVector2& v1, const XVector2& v2, float t) noexcept
{
	using namespace DirectX;
	t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
	t = t * t * (3.f - 2.f * t);
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);

	XVector2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XVector2::Barycentric(const XVector2& v1, const XVector2& v2, const XVector2& v3, float f, float g, XVector2& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR x3 = XMLoadFloat2(&v3);
	XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
	XMStoreFloat2(&result, X);
}

inline XVector2 XVector2::Barycentric(const XVector2& v1, const XVector2& v2, const XVector2& v3, float f, float g) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR x3 = XMLoadFloat2(&v3);
	XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

	XVector2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XVector2::CatmullRom(const XVector2& v1, const XVector2& v2, const XVector2& v3, const XVector2& v4, float t, XVector2& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR x3 = XMLoadFloat2(&v3);
	XMVECTOR x4 = XMLoadFloat2(&v4);
	XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
	XMStoreFloat2(&result, X);
}

inline XVector2 XVector2::CatmullRom(const XVector2& v1, const XVector2& v2, const XVector2& v3, const XVector2& v4, float t) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&v2);
	XMVECTOR x3 = XMLoadFloat2(&v3);
	XMVECTOR x4 = XMLoadFloat2(&v4);
	XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

	XVector2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XVector2::Hermite(const XVector2& v1, const XVector2& t1, const XVector2& v2, const XVector2& t2, float t, XVector2& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&t1);
	XMVECTOR x3 = XMLoadFloat2(&v2);
	XMVECTOR x4 = XMLoadFloat2(&t2);
	XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
	XMStoreFloat2(&result, X);
}

inline XVector2 XVector2::Hermite(const XVector2& v1, const XVector2& t1, const XVector2& v2, const XVector2& t2, float t) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat2(&v1);
	XMVECTOR x2 = XMLoadFloat2(&t1);
	XMVECTOR x3 = XMLoadFloat2(&v2);
	XMVECTOR x4 = XMLoadFloat2(&t2);
	XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

	XVector2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XVector2::Reflect(const XVector2& ivec, const XVector2& nvec, XVector2& result) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat2(&ivec);
	XMVECTOR n = XMLoadFloat2(&nvec);
	XMVECTOR X = XMVector2Reflect(i, n);
	XMStoreFloat2(&result, X);
}

inline XVector2 XVector2::Reflect(const XVector2& ivec, const XVector2& nvec) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat2(&ivec);
	XMVECTOR n = XMLoadFloat2(&nvec);
	XMVECTOR X = XMVector2Reflect(i, n);

	XVector2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XVector2::Refract(const XVector2& ivec, const XVector2& nvec, float refractionIndex, XVector2& result) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat2(&ivec);
	XMVECTOR n = XMLoadFloat2(&nvec);
	XMVECTOR X = XMVector2Refract(i, n, refractionIndex);
	XMStoreFloat2(&result, X);
}

inline XVector2 XVector2::Refract(const XVector2& ivec, const XVector2& nvec, float refractionIndex) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat2(&ivec);
	XMVECTOR n = XMLoadFloat2(&nvec);
	XMVECTOR X = XMVector2Refract(i, n, refractionIndex);

	XVector2 result;
	XMStoreFloat2(&result, X);
	return result;
}
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

// 4D vector
struct XVector4 : public DirectX::XMFLOAT4
{
	XVector4() noexcept : XMFLOAT4(0.f, 0.f, 0.f, 0.f) {}
	constexpr explicit XVector4(float ix) noexcept : XMFLOAT4(ix, ix, ix, ix) {}
	constexpr XVector4(float ix, float iy, float iz, float iw) noexcept : XMFLOAT4(ix, iy, iz, iw) {}
	explicit XVector4(_In_reads_(4) const float* pArray) noexcept : XMFLOAT4(pArray) {}
	XVector4(DirectX::FXMVECTOR V) noexcept { XMStoreFloat4(this, V); }
	XVector4(const XMFLOAT4& V) noexcept { this->x = V.x; this->y = V.y; this->z = V.z; this->w = V.w; }
	explicit XVector4(const DirectX::XMVECTORF32& F) noexcept { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

	XVector4(const XVector4&) = default;
	XVector4& operator=(const XVector4&) = default;

	XVector4(XVector4&&) = default;
	XVector4& operator=(XVector4&&) = default;

	operator DirectX::XMVECTOR() const  noexcept { return XMLoadFloat4(this); }

	// Comparison operators
	bool operator == (const XVector4& V) const noexcept;
	bool operator != (const XVector4& V) const noexcept;

	// Assignment operators
	XVector4& operator= (const DirectX::XMVECTORF32& F) noexcept { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
	XVector4& operator+= (const XVector4& V) noexcept;
	XVector4& operator-= (const XVector4& V) noexcept;
	XVector4& operator*= (const XVector4& V) noexcept;
	XVector4& operator*= (float S) noexcept;
	XVector4& operator/= (float S) noexcept;

	// Unary operators
	XVector4 operator+ () const noexcept { return *this; }
	XVector4 operator- () const noexcept;

	// Vector operations
	bool InBounds(const XVector4& Bounds) const noexcept;

	float Length() const noexcept;
	float LengthSquared() const noexcept;

	float Dot(const XVector4& V) const noexcept;
	void Cross(const XVector4& v1, const XVector4& v2, XVector4& result) const noexcept;
	XVector4 Cross(const XVector4& v1, const XVector4& v2) const noexcept;

	void Normalize() noexcept;
	void Normalize(XVector4& result) const noexcept;

	void Clamp(const XVector4& vmin, const XVector4& vmax) noexcept;
	void Clamp(const XVector4& vmin, const XVector4& vmax, XVector4& result) const noexcept;

	// Static functions
	static float Distance(const XVector4& v1, const XVector4& v2) noexcept;
	static float DistanceSquared(const XVector4& v1, const XVector4& v2) noexcept;

	static void Min(const XVector4& v1, const XVector4& v2, XVector4& result) noexcept;
	static XVector4 Min(const XVector4& v1, const XVector4& v2) noexcept;

	static void Max(const XVector4& v1, const XVector4& v2, XVector4& result) noexcept;
	static XVector4 Max(const XVector4& v1, const XVector4& v2) noexcept;

	static void Lerp(const XVector4& v1, const XVector4& v2, float t, XVector4& result) noexcept;
	static XVector4 Lerp(const XVector4& v1, const XVector4& v2, float t) noexcept;

	static void SmoothStep(const XVector4& v1, const XVector4& v2, float t, XVector4& result) noexcept;
	static XVector4 SmoothStep(const XVector4& v1, const XVector4& v2, float t) noexcept;

	static void Barycentric(const XVector4& v1, const XVector4& v2, const XVector4& v3, float f, float g, XVector4& result) noexcept;
	static XVector4 Barycentric(const XVector4& v1, const XVector4& v2, const XVector4& v3, float f, float g) noexcept;

	static void CatmullRom(const XVector4& v1, const XVector4& v2, const XVector4& v3, const XVector4& v4, float t, XVector4& result) noexcept;
	static XVector4 CatmullRom(const XVector4& v1, const XVector4& v2, const XVector4& v3, const XVector4& v4, float t) noexcept;

	static void Hermite(const XVector4& v1, const XVector4& t1, const XVector4& v2, const XVector4& t2, float t, XVector4& result) noexcept;
	static XVector4 Hermite(const XVector4& v1, const XVector4& t1, const XVector4& v2, const XVector4& t2, float t) noexcept;

	static void Reflect(const XVector4& ivec, const XVector4& nvec, XVector4& result) noexcept;
	static XVector4 Reflect(const XVector4& ivec, const XVector4& nvec) noexcept;

	static void Refract(const XVector4& ivec, const XVector4& nvec, float refractionIndex, XVector4& result) noexcept;
	static XVector4 Refract(const XVector4& ivec, const XVector4& nvec, float refractionIndex) noexcept;

	// Constants
	static const XVector4 Zero;
	static const XVector4 One;
	static const XVector4 UnitX;
	static const XVector4 UnitY;
	static const XVector4 UnitZ;
	static const XVector4 UnitW;
};


//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XVector4::operator == (const XVector4& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	return XMVector4Equal(v1, v2);
}

inline bool XVector4::operator != (const XVector4& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	return XMVector4NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline XVector4& XVector4::operator+= (const XVector4& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat4(this, X);
	return *this;
}

inline XVector4& XVector4::operator-= (const XVector4& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat4(this, X);
	return *this;
}

inline XVector4& XVector4::operator*= (const XVector4& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat4(this, X);
	return *this;
}

inline XVector4& XVector4::operator*= (float S) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat4(this, X);
	return *this;
}

inline XVector4& XVector4::operator/= (float S) noexcept
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat4(this, X);
	return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline XVector4 XVector4::operator- () const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR X = XMVectorNegate(v1);
	XVector4 R;
	XMStoreFloat4(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline XVector4 operator+ (const XVector4& V1, const XVector4& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XVector4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XVector4 operator- (const XVector4& V1, const XVector4& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XVector4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XVector4 operator* (const XVector4& V1, const XVector4& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XVector4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XVector4 operator* (const XVector4& V, float S) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XVector4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XVector4 operator/ (const XVector4& V1, const XVector4& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XVector4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XVector4 operator/ (const XVector4& V, float S) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XVector4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XVector4 operator* (float S, const XVector4& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XVector4 R;
	XMStoreFloat4(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool XVector4::InBounds(const XVector4& Bounds) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&Bounds);
	return XMVector4InBounds(v1, v2);
}

inline float XVector4::Length() const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR X = XMVector4Length(v1);
	return XMVectorGetX(X);
}

inline float XVector4::LengthSquared() const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR X = XMVector4LengthSq(v1);
	return XMVectorGetX(X);
}

inline float XVector4::Dot(const XVector4& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4Dot(v1, v2);
	return XMVectorGetX(X);
}

inline void XVector4::Cross(const XVector4& v1, const XVector4& v2, XVector4& result) const noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(this);
	XMVECTOR x2 = XMLoadFloat4(&v1);
	XMVECTOR x3 = XMLoadFloat4(&v2);
	XMVECTOR R = XMVector4Cross(x1, x2, x3);
	XMStoreFloat4(&result, R);
}

inline XVector4 XVector4::Cross(const XVector4& v1, const XVector4& v2) const noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(this);
	XMVECTOR x2 = XMLoadFloat4(&v1);
	XMVECTOR x3 = XMLoadFloat4(&v2);
	XMVECTOR R = XMVector4Cross(x1, x2, x3);

	XVector4 result;
	XMStoreFloat4(&result, R);
	return result;
}

inline void XVector4::Normalize() noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR X = XMVector4Normalize(v1);
	XMStoreFloat4(this, X);
}

inline void XVector4::Normalize(XVector4& result) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR X = XMVector4Normalize(v1);
	XMStoreFloat4(&result, X);
}

inline void XVector4::Clamp(const XVector4& vmin, const XVector4& vmax) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&vmin);
	XMVECTOR v3 = XMLoadFloat4(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat4(this, X);
}

inline void XVector4::Clamp(const XVector4& vmin, const XVector4& vmax, XVector4& result) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&vmin);
	XMVECTOR v3 = XMLoadFloat4(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat4(&result, X);
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float XVector4::Distance(const XVector4& v1, const XVector4& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR V = XMVectorSubtract(x2, x1);
	XMVECTOR X = XMVector4Length(V);
	return XMVectorGetX(X);
}

inline float XVector4::DistanceSquared(const XVector4& v1, const XVector4& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR V = XMVectorSubtract(x2, x1);
	XMVECTOR X = XMVector4LengthSq(V);
	return XMVectorGetX(X);
}

inline void XVector4::Min(const XVector4& v1, const XVector4& v2, XVector4& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR X = XMVectorMin(x1, x2);
	XMStoreFloat4(&result, X);
}

inline XVector4 XVector4::Min(const XVector4& v1, const XVector4& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR X = XMVectorMin(x1, x2);

	XVector4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XVector4::Max(const XVector4& v1, const XVector4& v2, XVector4& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR X = XMVectorMax(x1, x2);
	XMStoreFloat4(&result, X);
}

inline XVector4 XVector4::Max(const XVector4& v1, const XVector4& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR X = XMVectorMax(x1, x2);

	XVector4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XVector4::Lerp(const XVector4& v1, const XVector4& v2, float t, XVector4& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);
	XMStoreFloat4(&result, X);
}

inline XVector4 XVector4::Lerp(const XVector4& v1, const XVector4& v2, float t) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);

	XVector4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XVector4::SmoothStep(const XVector4& v1, const XVector4& v2, float t, XVector4& result) noexcept
{
	using namespace DirectX;
	t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
	t = t * t * (3.f - 2.f * t);
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);
	XMStoreFloat4(&result, X);
}

inline XVector4 XVector4::SmoothStep(const XVector4& v1, const XVector4& v2, float t) noexcept
{
	using namespace DirectX;
	t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
	t = t * t * (3.f - 2.f * t);
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);

	XVector4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XVector4::Barycentric(const XVector4& v1, const XVector4& v2, const XVector4& v3, float f, float g, XVector4& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR x3 = XMLoadFloat4(&v3);
	XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
	XMStoreFloat4(&result, X);
}

inline XVector4 XVector4::Barycentric(const XVector4& v1, const XVector4& v2, const XVector4& v3, float f, float g) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR x3 = XMLoadFloat4(&v3);
	XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

	XVector4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XVector4::CatmullRom(const XVector4& v1, const XVector4& v2, const XVector4& v3, const XVector4& v4, float t, XVector4& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR x3 = XMLoadFloat4(&v3);
	XMVECTOR x4 = XMLoadFloat4(&v4);
	XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
	XMStoreFloat4(&result, X);
}

inline XVector4 XVector4::CatmullRom(const XVector4& v1, const XVector4& v2, const XVector4& v3, const XVector4& v4, float t) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&v2);
	XMVECTOR x3 = XMLoadFloat4(&v3);
	XMVECTOR x4 = XMLoadFloat4(&v4);
	XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

	XVector4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XVector4::Hermite(const XVector4& v1, const XVector4& t1, const XVector4& v2, const XVector4& t2, float t, XVector4& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&t1);
	XMVECTOR x3 = XMLoadFloat4(&v2);
	XMVECTOR x4 = XMLoadFloat4(&t2);
	XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
	XMStoreFloat4(&result, X);
}

inline XVector4 XVector4::Hermite(const XVector4& v1, const XVector4& t1, const XVector4& v2, const XVector4& t2, float t) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(&v1);
	XMVECTOR x2 = XMLoadFloat4(&t1);
	XMVECTOR x3 = XMLoadFloat4(&v2);
	XMVECTOR x4 = XMLoadFloat4(&t2);
	XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

	XVector4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XVector4::Reflect(const XVector4& ivec, const XVector4& nvec, XVector4& result) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat4(&ivec);
	XMVECTOR n = XMLoadFloat4(&nvec);
	XMVECTOR X = XMVector4Reflect(i, n);
	XMStoreFloat4(&result, X);
}

inline XVector4 XVector4::Reflect(const XVector4& ivec, const XVector4& nvec) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat4(&ivec);
	XMVECTOR n = XMLoadFloat4(&nvec);
	XMVECTOR X = XMVector4Reflect(i, n);

	XVector4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XVector4::Refract(const XVector4& ivec, const XVector4& nvec, float refractionIndex, XVector4& result) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat4(&ivec);
	XMVECTOR n = XMLoadFloat4(&nvec);
	XMVECTOR X = XMVector4Refract(i, n, refractionIndex);
	XMStoreFloat4(&result, X);
}

inline XVector4 XVector4::Refract(const XVector4& ivec, const XVector4& nvec, float refractionIndex) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat4(&ivec);
	XMVECTOR n = XMLoadFloat4(&nvec);
	XMVECTOR X = XMVector4Refract(i, n, refractionIndex);

	XVector4 result;
	XMStoreFloat4(&result, X);
	return result;
}
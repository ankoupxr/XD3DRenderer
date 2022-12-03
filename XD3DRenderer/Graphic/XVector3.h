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

// 3D vector
struct XVector3 : public DirectX::XMFLOAT3
{
	XVector3() noexcept : XMFLOAT3(0.f, 0.f, 0.f) {}
	constexpr explicit XVector3(float ix) noexcept : XMFLOAT3(ix, ix, ix) {}
	constexpr XVector3(float ix, float iy, float iz) noexcept : XMFLOAT3(ix, iy, iz) {}
	explicit XVector3(_In_reads_(3) const float* pArray) noexcept : XMFLOAT3(pArray) {}
	XVector3(DirectX::FXMVECTOR V) noexcept { XMStoreFloat3(this, V); }
	XVector3(const XMFLOAT3& V) noexcept { this->x = V.x; this->y = V.y; this->z = V.z; }
	explicit XVector3(const DirectX::XMVECTORF32& F) noexcept { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; }

	XVector3(const XVector3&) = default;
	XVector3& operator=(const XVector3&) = default;

	XVector3(XVector3&&) = default;
	XVector3& operator=(XVector3&&) = default;

	operator DirectX::XMVECTOR() const noexcept { return XMLoadFloat3(this); }

	// Access operators
	float operator [](int i) const noexcept
	{
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	float& operator [](int i) noexcept
	{
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	// Comparison operators
	bool operator == (const XVector3& V) const noexcept;
	bool operator != (const XVector3& V) const noexcept;

	// Assignment operators
	XVector3& operator= (const DirectX::XMVECTORF32& F) noexcept { x = F.f[0]; y = F.f[1]; z = F.f[2]; return *this; }
	XVector3& operator+= (const XVector3& V) noexcept;
	XVector3& operator-= (const XVector3& V) noexcept;
	XVector3& operator*= (const XVector3& V) noexcept;
	XVector3& operator*= (float S) noexcept;
	XVector3& operator/= (float S) noexcept;

	// Unary operators
	XVector3 operator+ () const noexcept { return *this; }
	XVector3 operator- () const noexcept;

	// Vector operations
	bool InBounds(const XVector3& Bounds) const noexcept;

	float Length() const noexcept;
	float LengthSquared() const noexcept;

	float Dot(const XVector3& V) const noexcept;
	void Cross(const XVector3& V, XVector3& result) const noexcept;
	XVector3 Cross(const XVector3& V) const noexcept;

	void Normalize() noexcept;
	void Normalize(XVector3& result) const noexcept;

	void Clamp(const XVector3& vmin, const XVector3& vmax) noexcept;
	void Clamp(const XVector3& vmin, const XVector3& vmax, XVector3& result) const noexcept;

	// Static functions
	static float Distance(const XVector3& v1, const XVector3& v2) noexcept;
	static float DistanceSquared(const XVector3& v1, const XVector3& v2) noexcept;

	static void Min(const XVector3& v1, const XVector3& v2, XVector3& result) noexcept;
	static XVector3 Min(const XVector3& v1, const XVector3& v2) noexcept;

	static void Max(const XVector3& v1, const XVector3& v2, XVector3& result) noexcept;
	static XVector3 Max(const XVector3& v1, const XVector3& v2) noexcept;

	static void Lerp(const XVector3& v1, const XVector3& v2, float t, XVector3& result) noexcept;
	static XVector3 Lerp(const XVector3& v1, const XVector3& v2, float t) noexcept;

	static void SmoothStep(const XVector3& v1, const XVector3& v2, float t, XVector3& result) noexcept;
	static XVector3 SmoothStep(const XVector3& v1, const XVector3& v2, float t) noexcept;

	static void Barycentric(const XVector3& v1, const XVector3& v2, const XVector3& v3, float f, float g, XVector3& result) noexcept;
	static XVector3 Barycentric(const XVector3& v1, const XVector3& v2, const XVector3& v3, float f, float g) noexcept;

	static void CatmullRom(const XVector3& v1, const XVector3& v2, const XVector3& v3, const XVector3& v4, float t, XVector3& result) noexcept;
	static XVector3 CatmullRom(const XVector3& v1, const XVector3& v2, const XVector3& v3, const XVector3& v4, float t) noexcept;

	static void Hermite(const XVector3& v1, const XVector3& t1, const XVector3& v2, const XVector3& t2, float t, XVector3& result) noexcept;
	static XVector3 Hermite(const XVector3& v1, const XVector3& t1, const XVector3& v2, const XVector3& t2, float t) noexcept;

	static void Reflect(const XVector3& ivec, const XVector3& nvec, XVector3& result) noexcept;
	static XVector3 Reflect(const XVector3& ivec, const XVector3& nvec) noexcept;

	static void Refract(const XVector3& ivec, const XVector3& nvec, float refractionIndex, XVector3& result) noexcept;
	static XVector3 Refract(const XVector3& ivec, const XVector3& nvec, float refractionIndex) noexcept;

	// Constants
	static const XVector3 Zero;
	static const XVector3 One;
	static const XVector3 UnitX;
	static const XVector3 UnitY;
	static const XVector3 UnitZ;
	static const XVector3 Up;
	static const XVector3 Down;
	static const XVector3 Right;
	static const XVector3 Left;
	static const XVector3 Forward;
	static const XVector3 Backward;
};

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XVector3::operator == (const XVector3& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	return XMVector3Equal(v1, v2);
}

inline bool XVector3::operator != (const XVector3& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	return XMVector3NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline XVector3& XVector3::operator+= (const XVector3& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat3(this, X);
	return *this;
}

inline XVector3& XVector3::operator-= (const XVector3& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat3(this, X);
	return *this;
}

inline XVector3& XVector3::operator*= (const XVector3& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat3(this, X);
	return *this;
}

inline XVector3& XVector3::operator*= (float S) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat3(this, X);
	return *this;
}

inline XVector3& XVector3::operator/= (float S) noexcept
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat3(this, X);
	return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline XVector3 XVector3::operator- () const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR X = XMVectorNegate(v1);
	XVector3 R;
	XMStoreFloat3(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline XVector3 operator+ (const XVector3& V1, const XVector3& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XVector3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XVector3 operator- (const XVector3& V1, const XVector3& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XVector3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XVector3 operator* (const XVector3& V1, const XVector3& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XVector3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XVector3 operator* (const XVector3& V, float S) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XVector3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XVector3 operator/ (const XVector3& V1, const XVector3& V2) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XVector3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XVector3 operator/ (const XVector3& V, float S) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XVector3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XVector3 operator* (float S, const XVector3& V) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XVector3 R;
	XMStoreFloat3(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool XVector3::InBounds(const XVector3& Bounds) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&Bounds);
	return XMVector3InBounds(v1, v2);
}

inline float XVector3::Length() const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR X = XMVector3Length(v1);
	return XMVectorGetX(X);
}

inline float XVector3::LengthSquared() const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR X = XMVector3LengthSq(v1);
	return XMVectorGetX(X);
}

inline float XVector3::Dot(const XVector3& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3Dot(v1, v2);
	return XMVectorGetX(X);
}

inline void XVector3::Cross(const XVector3& V, XVector3& result) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR R = XMVector3Cross(v1, v2);
	XMStoreFloat3(&result, R);
}

inline XVector3 XVector3::Cross(const XVector3& V) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR R = XMVector3Cross(v1, v2);

	XVector3 result;
	XMStoreFloat3(&result, R);
	return result;
}

inline void XVector3::Normalize() noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR X = XMVector3Normalize(v1);
	XMStoreFloat3(this, X);
}

inline void XVector3::Normalize(XVector3& result) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR X = XMVector3Normalize(v1);
	XMStoreFloat3(&result, X);
}

inline void XVector3::Clamp(const XVector3& vmin, const XVector3& vmax) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&vmin);
	XMVECTOR v3 = XMLoadFloat3(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat3(this, X);
}

inline void XVector3::Clamp(const XVector3& vmin, const XVector3& vmax, XVector3& result) const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&vmin);
	XMVECTOR v3 = XMLoadFloat3(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat3(&result, X);
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float XVector3::Distance(const XVector3& v1, const XVector3& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR V = XMVectorSubtract(x2, x1);
	XMVECTOR X = XMVector3Length(V);
	return XMVectorGetX(X);
}

inline float XVector3::DistanceSquared(const XVector3& v1, const XVector3& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR V = XMVectorSubtract(x2, x1);
	XMVECTOR X = XMVector3LengthSq(V);
	return XMVectorGetX(X);
}

inline void XVector3::Min(const XVector3& v1, const XVector3& v2, XVector3& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR X = XMVectorMin(x1, x2);
	XMStoreFloat3(&result, X);
}

inline XVector3 XVector3::Min(const XVector3& v1, const XVector3& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR X = XMVectorMin(x1, x2);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XVector3::Max(const XVector3& v1, const XVector3& v2, XVector3& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR X = XMVectorMax(x1, x2);
	XMStoreFloat3(&result, X);
}

inline XVector3 XVector3::Max(const XVector3& v1, const XVector3& v2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR X = XMVectorMax(x1, x2);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XVector3::Lerp(const XVector3& v1, const XVector3& v2, float t, XVector3& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);
	XMStoreFloat3(&result, X);
}

inline XVector3 XVector3::Lerp(const XVector3& v1, const XVector3& v2, float t) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XVector3::SmoothStep(const XVector3& v1, const XVector3& v2, float t, XVector3& result) noexcept
{
	using namespace DirectX;
	t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
	t = t * t * (3.f - 2.f * t);
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);
	XMStoreFloat3(&result, X);
}

inline XVector3 XVector3::SmoothStep(const XVector3& v1, const XVector3& v2, float t) noexcept
{
	using namespace DirectX;
	t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
	t = t * t * (3.f - 2.f * t);
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XVector3::Barycentric(const XVector3& v1, const XVector3& v2, const XVector3& v3, float f, float g, XVector3& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR x3 = XMLoadFloat3(&v3);
	XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
	XMStoreFloat3(&result, X);
}

inline XVector3 XVector3::Barycentric(const XVector3& v1, const XVector3& v2, const XVector3& v3, float f, float g) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR x3 = XMLoadFloat3(&v3);
	XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XVector3::CatmullRom(const XVector3& v1, const XVector3& v2, const XVector3& v3, const XVector3& v4, float t, XVector3& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR x3 = XMLoadFloat3(&v3);
	XMVECTOR x4 = XMLoadFloat3(&v4);
	XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
	XMStoreFloat3(&result, X);
}

inline XVector3 XVector3::CatmullRom(const XVector3& v1, const XVector3& v2, const XVector3& v3, const XVector3& v4, float t) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR x3 = XMLoadFloat3(&v3);
	XMVECTOR x4 = XMLoadFloat3(&v4);
	XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XVector3::Hermite(const XVector3& v1, const XVector3& t1, const XVector3& v2, const XVector3& t2, float t, XVector3& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&t1);
	XMVECTOR x3 = XMLoadFloat3(&v2);
	XMVECTOR x4 = XMLoadFloat3(&t2);
	XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
	XMStoreFloat3(&result, X);
}

inline XVector3 XVector3::Hermite(const XVector3& v1, const XVector3& t1, const XVector3& v2, const XVector3& t2, float t) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&t1);
	XMVECTOR x3 = XMLoadFloat3(&v2);
	XMVECTOR x4 = XMLoadFloat3(&t2);
	XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XVector3::Reflect(const XVector3& ivec, const XVector3& nvec, XVector3& result) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat3(&ivec);
	XMVECTOR n = XMLoadFloat3(&nvec);
	XMVECTOR X = XMVector3Reflect(i, n);
	XMStoreFloat3(&result, X);
}

inline XVector3 XVector3::Reflect(const XVector3& ivec, const XVector3& nvec) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat3(&ivec);
	XMVECTOR n = XMLoadFloat3(&nvec);
	XMVECTOR X = XMVector3Reflect(i, n);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XVector3::Refract(const XVector3& ivec, const XVector3& nvec, float refractionIndex, XVector3& result) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat3(&ivec);
	XMVECTOR n = XMLoadFloat3(&nvec);
	XMVECTOR X = XMVector3Refract(i, n, refractionIndex);
	XMStoreFloat3(&result, X);
}

inline XVector3 XVector3::Refract(const XVector3& ivec, const XVector3& nvec, float refractionIndex) noexcept
{
	using namespace DirectX;
	XMVECTOR i = XMLoadFloat3(&ivec);
	XMVECTOR n = XMLoadFloat3(&nvec);
	XMVECTOR X = XMVector3Refract(i, n, refractionIndex);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}
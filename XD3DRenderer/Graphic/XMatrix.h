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
#include <string.h>
#include "XVector3.h"
#include "XVector4.h"

// 4x4 Matrix (use left-handed cooordinates !!!)
struct XMatrix : public DirectX::XMFLOAT4X4
{
	XMatrix() noexcept
		: DirectX::XMFLOAT4X4(1.f, 0, 0, 0,
			0, 1.f, 0, 0,
			0, 0, 1.f, 0,
			0, 0, 0, 1.f) {}
	constexpr XMatrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) noexcept
		: XMFLOAT4X4(m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33) {}
	explicit XMatrix(const XVector3& r0, const XVector3& r1, const XVector3& r2) noexcept
		: XMFLOAT4X4(r0.x, r0.y, r0.z, 0,
			r1.x, r1.y, r1.z, 0,
			r2.x, r2.y, r2.z, 0,
			0, 0, 0, 1.f) {}
	explicit XMatrix(const XVector4& r0, const XVector4& r1, const XVector4& r2, const XVector4& r3) noexcept
		: XMFLOAT4X4(r0.x, r0.y, r0.z, r0.w,
			r1.x, r1.y, r1.z, r1.w,
			r2.x, r2.y, r2.z, r2.w,
			r3.x, r3.y, r3.z, r3.w) {}
	XMatrix(const DirectX::XMFLOAT4X4& M) noexcept { memcpy_s(this, sizeof(float) * 16, &M, sizeof(XMFLOAT4X4)); }
	XMatrix(const DirectX::XMFLOAT3X3& M) noexcept;
	XMatrix(const DirectX::XMFLOAT4X3& M) noexcept;

	explicit XMatrix(_In_reads_(16) const float* pArray) noexcept : XMFLOAT4X4(pArray) {}
	XMatrix(DirectX::CXMMATRIX M) noexcept { DirectX::XMStoreFloat4x4(this, M); }

	XMatrix(const XMatrix&) = default;
	XMatrix& operator=(const XMatrix&) = default;

	XMatrix(XMatrix&&) = default;
	XMatrix& operator=(XMatrix&&) = default;

	operator DirectX::XMMATRIX() const noexcept { return DirectX::XMLoadFloat4x4(this); }

	// Comparison operators
	bool operator == (const XMatrix& M) const noexcept;
	bool operator != (const XMatrix& M) const noexcept;

	// Assignment operators
	XMatrix& operator= (const DirectX::XMFLOAT3X3& M) noexcept;
	XMatrix& operator= (const DirectX::XMFLOAT4X3& M) noexcept;
	XMatrix& operator+= (const XMatrix& M) noexcept;
	XMatrix& operator-= (const XMatrix& M) noexcept;
	XMatrix& operator*= (const XMatrix& M) noexcept;
	XMatrix& operator*= (float S) noexcept;
	XMatrix& operator/= (float S) noexcept;

	XMatrix& operator/= (const XMatrix& M) noexcept;
	// Element-wise divide

	// Unary operators
	XMatrix operator+ () const noexcept { return *this; }
	XMatrix operator- () const noexcept;

	// Properties
	XVector3 Up() const noexcept { return XVector3(_21, _22, _23); }
	void Up(const XVector3& v) noexcept { _21 = v.x; _22 = v.y; _23 = v.z; }

	XVector3 Down() const  noexcept { return XVector3(-_21, -_22, -_23); }
	void Down(const XVector3& v) noexcept { _21 = -v.x; _22 = -v.y; _23 = -v.z; }

	XVector3 Right() const noexcept { return XVector3(_11, _12, _13); }
	void Right(const XVector3& v) noexcept { _11 = v.x; _12 = v.y; _13 = v.z; }

	XVector3 Left() const noexcept { return XVector3(-_11, -_12, -_13); }
	void Left(const XVector3& v) noexcept { _11 = -v.x; _12 = -v.y; _13 = -v.z; }

	XVector3 Forward() const noexcept { return XVector3(-_31, -_32, -_33); }
	void Forward(const XVector3& v) noexcept { _31 = -v.x; _32 = -v.y; _33 = -v.z; }

	XVector3 Backward() const noexcept { return XVector3(_31, _32, _33); }
	void Backward(const XVector3& v) noexcept { _31 = v.x; _32 = v.y; _33 = v.z; }

	XVector3 Translation() const  noexcept { return XVector3(_41, _42, _43); }
	void Translation(const XVector3& v) noexcept { _41 = v.x; _42 = v.y; _43 = v.z; }

	// Matrix operations
	XMatrix Transpose() const noexcept;
	void Transpose(XMatrix& result) const noexcept;

	XMatrix Invert() const noexcept;
	void Invert(XMatrix& result) const noexcept;

	float Determinant() const noexcept;

	// Static functions
	static XMatrix CreateTranslation(const XVector3& position) noexcept;
	static XMatrix CreateTranslation(float x, float y, float z) noexcept;

	static XMatrix CreateScale(const XVector3& scales) noexcept;
	static XMatrix CreateScale(float xs, float ys, float zs) noexcept;
	static XMatrix CreateScale(float scale) noexcept;

	static XMatrix CreateRotationX(float radians) noexcept;
	static XMatrix CreateRotationY(float radians) noexcept;
	static XMatrix CreateRotationZ(float radians) noexcept;

	static XMatrix CreateFromAxisAngle(const XVector3& axis, float angle) noexcept;

	static XMatrix CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane) noexcept;
	static XMatrix CreatePerspective(float width, float height, float nearPlane, float farPlane) noexcept;
	static XMatrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane) noexcept;
	static XMatrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane) noexcept;
	static XMatrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane) noexcept;

	static XMatrix CreateLookAt(const XVector3& position, const XVector3& target, const XVector3& up) noexcept;
	static XMatrix CreateWorld(const XVector3& position, const XVector3& forward, const XVector3& up) noexcept;

	static XMatrix CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept;

	static void Lerp(const XMatrix& M1, const XMatrix& M2, float t, XMatrix& result) noexcept;
	static XMatrix Lerp(const XMatrix& M1, const XMatrix& M2, float t) noexcept;

	XVector3 Transform(const XVector3& v) noexcept;
	XVector3 TransformNormal(const XVector3& v) noexcept;


	// Constants
	static const XMatrix Identity;
};


//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XMatrix::operator == (const XMatrix& M) const noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	return (XMVector4Equal(x1, y1)
		&& XMVector4Equal(x2, y2)
		&& XMVector4Equal(x3, y3)
		&& XMVector4Equal(x4, y4)) != 0;
}

inline bool XMatrix::operator != (const XMatrix& M) const noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	return (XMVector4NotEqual(x1, y1)
		|| XMVector4NotEqual(x2, y2)
		|| XMVector4NotEqual(x3, y3)
		|| XMVector4NotEqual(x4, y4)) != 0;
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline XMatrix::XMatrix(const DirectX::XMFLOAT3X3& M) noexcept
{
	_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
	_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
	_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
	_41 = 0.f;   _42 = 0.f;   _43 = 0.f;   _44 = 1.f;
}

inline XMatrix::XMatrix(const DirectX::XMFLOAT4X3& M) noexcept
{
	_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
	_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
	_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
	_41 = M._41; _42 = M._42; _43 = M._43; _44 = 1.f;
}

inline XMatrix& XMatrix::operator= (const DirectX::XMFLOAT3X3& M) noexcept
{
	_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
	_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
	_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
	_41 = 0.f;   _42 = 0.f;   _43 = 0.f;   _44 = 1.f;
	return *this;
}

inline XMatrix& XMatrix::operator= (const DirectX::XMFLOAT4X3& M) noexcept
{
	_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
	_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
	_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
	_41 = M._41; _42 = M._42; _43 = M._43; _44 = 1.f;
	return *this;
}

inline XMatrix& XMatrix::operator+= (const XMatrix& M) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorAdd(x1, y1);
	x2 = XMVectorAdd(x2, y2);
	x3 = XMVectorAdd(x3, y3);
	x4 = XMVectorAdd(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline XMatrix& XMatrix::operator-= (const XMatrix& M) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorSubtract(x1, y1);
	x2 = XMVectorSubtract(x2, y2);
	x3 = XMVectorSubtract(x3, y3);
	x4 = XMVectorSubtract(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline XMatrix& XMatrix::operator*= (const XMatrix& M) noexcept
{
	using namespace DirectX;
	XMMATRIX M1 = XMLoadFloat4x4(this);
	XMMATRIX M2 = XMLoadFloat4x4(&M);
	XMMATRIX X = XMMatrixMultiply(M1, M2);
	DirectX::XMStoreFloat4x4(this, X);
	return *this;
}

inline XMatrix& XMatrix::operator*= (float S) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	x1 = XMVectorScale(x1, S);
	x2 = XMVectorScale(x2, S);
	x3 = XMVectorScale(x3, S);
	x4 = XMVectorScale(x4, S);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline XMatrix& XMatrix::operator/= (float S) noexcept
{
	using namespace DirectX;
	assert(S != 0.f);
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	float rs = 1.f / S;

	x1 = XMVectorScale(x1, rs);
	x2 = XMVectorScale(x2, rs);
	x3 = XMVectorScale(x3, rs);
	x4 = XMVectorScale(x4, rs);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline XMatrix& XMatrix::operator/= (const XMatrix& M) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorDivide(x1, y1);
	x2 = XMVectorDivide(x2, y2);
	x3 = XMVectorDivide(x3, y3);
	x4 = XMVectorDivide(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline XMatrix XMatrix::operator- () const noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	v1 = XMVectorNegate(v1);
	v2 = XMVectorNegate(v2);
	v3 = XMVectorNegate(v3);
	v4 = XMVectorNegate(v4);

	XMatrix R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), v1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), v2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), v3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), v4);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline XMatrix operator+ (const XMatrix& M1, const XMatrix& M2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

	x1 = XMVectorAdd(x1, y1);
	x2 = XMVectorAdd(x2, y2);
	x3 = XMVectorAdd(x3, y3);
	x4 = XMVectorAdd(x4, y4);

	XMatrix R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline XMatrix operator- (const XMatrix& M1, const XMatrix& M2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

	x1 = XMVectorSubtract(x1, y1);
	x2 = XMVectorSubtract(x2, y2);
	x3 = XMVectorSubtract(x3, y3);
	x4 = XMVectorSubtract(x4, y4);

	XMatrix R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline XMatrix operator* (const XMatrix& M1, const XMatrix& M2) noexcept
{
	using namespace DirectX;
	XMMATRIX m1 = XMLoadFloat4x4(&M1);
	XMMATRIX m2 = XMLoadFloat4x4(&M2);
	XMMATRIX X = XMMatrixMultiply(m1, m2);

	XMatrix R;
	DirectX::XMStoreFloat4x4(&R, X);
	return R;
}

inline XMatrix operator* (const XMatrix& M, float S) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorScale(x1, S);
	x2 = XMVectorScale(x2, S);
	x3 = XMVectorScale(x3, S);
	x4 = XMVectorScale(x4, S);

	XMatrix R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline XMatrix operator/ (const XMatrix& M, float S) noexcept
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	float rs = 1.f / S;

	x1 = XMVectorScale(x1, rs);
	x2 = XMVectorScale(x2, rs);
	x3 = XMVectorScale(x3, rs);
	x4 = XMVectorScale(x4, rs);

	XMatrix R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline XMatrix operator/ (const XMatrix& M1, const XMatrix& M2) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

	x1 = XMVectorDivide(x1, y1);
	x2 = XMVectorDivide(x2, y2);
	x3 = XMVectorDivide(x3, y3);
	x4 = XMVectorDivide(x4, y4);

	XMatrix R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline XMatrix operator* (float S, const XMatrix& M) noexcept
{
	using namespace DirectX;

	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorScale(x1, S);
	x2 = XMVectorScale(x2, S);
	x3 = XMVectorScale(x3, S);
	x4 = XMVectorScale(x4, S);

	XMatrix R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

//------------------------------------------------------------------------------
// XMatrix operations
//------------------------------------------------------------------------------
inline XMatrix XMatrix::Transpose() const noexcept
{
	using namespace DirectX;
	XMMATRIX M = XMLoadFloat4x4(this);
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixTranspose(M));
	return R;
}

inline void XMatrix::Transpose(XMatrix& result) const noexcept
{
	using namespace DirectX;
	XMMATRIX M = XMLoadFloat4x4(this);
	XMStoreFloat4x4(&result, XMMatrixTranspose(M));
}

inline XMatrix XMatrix::Invert() const noexcept
{
	using namespace DirectX;
	XMMATRIX M = XMLoadFloat4x4(this);
	XMatrix R;
	XMVECTOR det;
	XMStoreFloat4x4(&R, XMMatrixInverse(&det, M));
	return R;
}

inline void XMatrix::Invert(XMatrix& result) const noexcept
{
	using namespace DirectX;
	XMMATRIX M = XMLoadFloat4x4(this);
	XMVECTOR det;
	XMStoreFloat4x4(&result, XMMatrixInverse(&det, M));
}

inline float XMatrix::Determinant() const noexcept
{
	using namespace DirectX;
	XMMATRIX M = XMLoadFloat4x4(this);
	return XMVectorGetX(XMMatrixDeterminant(M));
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline XMatrix XMatrix::CreateTranslation(const XVector3& position) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixTranslation(position.x, position.y, position.z));
	return R;
}

inline XMatrix XMatrix::CreateTranslation(float x, float y, float z) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixTranslation(x, y, z));
	return R;
}

inline XMatrix XMatrix::CreateScale(const XVector3& scales) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixScaling(scales.x, scales.y, scales.z));
	return R;
}

inline XMatrix XMatrix::CreateScale(float xs, float ys, float zs) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixScaling(xs, ys, zs));
	return R;
}

inline XMatrix XMatrix::CreateScale(float scale) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixScaling(scale, scale, scale));
	return R;
}

inline XMatrix XMatrix::CreateRotationX(float radians) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixRotationX(radians));
	return R;
}

inline XMatrix XMatrix::CreateRotationY(float radians) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixRotationY(radians));
	return R;
}

inline XMatrix XMatrix::CreateRotationZ(float radians) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixRotationZ(radians));
	return R;
}

inline XMatrix XMatrix::CreateFromAxisAngle(const XVector3& axis, float angle) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMVECTOR a = XMLoadFloat3(&axis);
	XMStoreFloat4x4(&R, XMMatrixRotationAxis(a, angle));
	return R;
}

inline XMatrix XMatrix::CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane));

	return R;
}

inline XMatrix XMatrix::CreatePerspective(float width, float height, float nearPlane, float farPlane) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixPerspectiveLH(width, height, nearPlane, farPlane));
	return R;
}

inline XMatrix XMatrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixPerspectiveOffCenterLH(left, right, bottom, top, nearPlane, farPlane));
	return R;
}

inline XMatrix XMatrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixOrthographicLH(width, height, zNearPlane, zFarPlane));
	return R;
}

inline XMatrix XMatrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixOrthographicOffCenterLH(left, right, bottom, top, zNearPlane, zFarPlane));

	return R;
}

inline XMatrix XMatrix::CreateLookAt(const XVector3& eye, const XVector3& target, const XVector3& up) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMVECTOR eyev = XMLoadFloat3(&eye);
	XMVECTOR targetv = XMLoadFloat3(&target);
	XMVECTOR upv = XMLoadFloat3(&up);

	XMStoreFloat4x4(&R, XMMatrixLookAtLH(eyev, targetv, upv));

	return R;
}

inline XMatrix XMatrix::CreateWorld(const XVector3& position, const XVector3& forward, const XVector3& up) noexcept
{
	using namespace DirectX;
	XMVECTOR zaxis = XMVector3Normalize(XMVectorNegate(XMLoadFloat3(&forward)));
	XMVECTOR yaxis = XMLoadFloat3(&up);
	XMVECTOR xaxis = XMVector3Normalize(XMVector3Cross(yaxis, zaxis));
	yaxis = XMVector3Cross(zaxis, xaxis);

	XMatrix R;
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._11), xaxis);
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._21), yaxis);
	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._31), zaxis);
	R._14 = R._24 = R._34 = 0.f;
	R._41 = position.x; R._42 = position.y; R._43 = position.z;
	R._44 = 1.f;
	return R;
}

inline XMatrix XMatrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept
{
	using namespace DirectX;
	XMatrix R;
	XMStoreFloat4x4(&R, XMMatrixRotationRollPitchYaw(pitch, yaw, roll));
	return R;
}

inline void XMatrix::Lerp(const XMatrix& M1, const XMatrix& M2, float t, XMatrix& result) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

	x1 = XMVectorLerp(x1, y1, t);
	x2 = XMVectorLerp(x2, y2, t);
	x3 = XMVectorLerp(x3, y3, t);
	x4 = XMVectorLerp(x4, y4, t);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
}

inline XMatrix XMatrix::Lerp(const XMatrix& M1, const XMatrix& M2, float t) noexcept
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

	x1 = XMVectorLerp(x1, y1, t);
	x2 = XMVectorLerp(x2, y2, t);
	x3 = XMVectorLerp(x3, y3, t);
	x4 = XMVectorLerp(x4, y4, t);

	XMatrix result;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
	return result;
}

inline XVector3 XMatrix::Transform(const XVector3& v) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&v);
	XMMATRIX M = XMLoadFloat4x4(this);
	XMVECTOR X = XMVector3TransformCoord(v1, M);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline XVector3 XMatrix::TransformNormal(const XVector3& v) noexcept
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&v);
	XMMATRIX M = XMLoadFloat4x4(this);
	XMVECTOR X = XMVector3TransformNormal(v1, M);

	XVector3 result;
	XMStoreFloat3(&result, X);
	return result;
}
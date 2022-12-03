#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
	SetLens(0.25f * TMath::Pi, 1.0f, 0.1f, 100.0f);
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::SetWorldLocation(const XVector3& Location)
{
	WorldTransform.Location = Location;
	ViewDirty = true;
}

float CameraComponent::GetNearZ()const
{
	return NearZ;
}

float CameraComponent::GetFarZ()const
{
	return FarZ;
}

float CameraComponent::GetAspect()const
{
	return Aspect;
}

float CameraComponent::GetFovY()const
{
	return FovY;
}

float CameraComponent::GetFovX()const
{
	float halfWidth = 0.5f * GetNearWindowWidth();
	return float(2.0f * atan(halfWidth / NearZ));
}

float CameraComponent::GetNearWindowWidth()const
{
	return Aspect * NearWindowHeight;
}

float CameraComponent::GetNearWindowHeight()const
{
	return NearWindowHeight;
}

float CameraComponent::GetFarWindowWidth()const
{
	return Aspect * FarWindowHeight;
}

float CameraComponent::GetFarWindowHeight()const
{
	return FarWindowHeight;
}

void CameraComponent::SetLens(float fovY, float aspect, float zn, float zf)
{
	// cache properties
	FovY = fovY;
	Aspect = aspect;
	NearZ = zn;
	FarZ = zf;

	NearWindowHeight = 2.0f * NearZ * tanf(0.5f * FovY);
	FarWindowHeight = 2.0f * FarZ * tanf(0.5f * FovY);

	Proj = XMatrix::CreatePerspectiveFieldOfView(FovY, Aspect, NearZ, FarZ);
}

void CameraComponent::LookAt(const XVector3& pos, const XVector3& target, const XVector3& up)
{
	XVector3 L = target - pos;
	L.Normalize();
	XVector3 R = up.Cross(L);
	R.Normalize();
	XVector3 U = L.Cross(R);

	WorldTransform.Location = pos;
	Look = L;
	Right = R;
	Up = U;

	ViewDirty = true;
}


XMatrix CameraComponent::GetView()const
{
	assert(!ViewDirty);
	return View;
}

XMatrix CameraComponent::GetProj()const
{
	return Proj;
}

void CameraComponent::MoveRight(float Dist)
{
	WorldTransform.Location += Dist * Right;

	ViewDirty = true;
}

void CameraComponent::MoveForward(float Dist)
{
	WorldTransform.Location += Dist * Look;

	ViewDirty = true;
}

void CameraComponent::MoveUp(float Dist)
{
	WorldTransform.Location += Dist * Up;

	ViewDirty = true;
}

void CameraComponent::Pitch(float Degrees)
{
	float Radians = TMath::DegreesToRadians(Degrees);

	// Rotate up and look vector about the right vector.
	XMatrix R = XMatrix::CreateFromAxisAngle(Right, Radians);

	Up = R.TransformNormal(Up);
	Look = R.TransformNormal(Look);

	ViewDirty = true;
}

void CameraComponent::RotateY(float Degrees)
{
	float Radians = TMath::DegreesToRadians(Degrees);

	// Rotate the basis vectors about the world y-axis.
	XMatrix R = XMatrix::CreateRotationY(Radians);

	Right = R.TransformNormal(Right);
	Up = R.TransformNormal(Up);
	Look = R.TransformNormal(Look);

	ViewDirty = true;
}

void CameraComponent::UpdateViewMatrix()
{
	if (ViewDirty)
	{
		// Keep camera's axes orthogonal to each other and of unit length.
		Look.Normalize();
		Up = Look.Cross(Right);
		Up.Normalize();

		// Up, Look already ortho-normal, so no need to normalize cross product.
		Right = Up.Cross(Look);

		// Fill in the view matrix entries.
		float x = -WorldTransform.Location.Dot(Right);
		float y = -WorldTransform.Location.Dot(Up);
		float z = -WorldTransform.Location.Dot(Look);

		View(0, 0) = Right.x;
		View(1, 0) = Right.y;
		View(2, 0) = Right.z;
		View(3, 0) = x;

		View(0, 1) = Up.x;
		View(1, 1) = Up.y;
		View(2, 1) = Up.z;
		View(3, 1) = y;

		View(0, 2) = Look.x;
		View(1, 2) = Look.y;
		View(2, 2) = Look.z;
		View(3, 2) = z;

		View(0, 3) = 0.0f;
		View(1, 3) = 0.0f;
		View(2, 3) = 0.0f;
		View(3, 3) = 1.0f;

		ViewDirty = false;
	}
}

void CameraComponent::SetPrevViewProj(const XMatrix& VP)
{
	PrevViewProj = VP;
}

XMatrix CameraComponent::GetPrevViewProj() const
{
	return PrevViewProj;
}
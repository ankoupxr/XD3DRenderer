#pragma once

#include "XMath.h"

struct XRotator
{
	float Roll;
	float Pitch;
	float Yaw;

	XRotator()
		:Roll(0.0f), Pitch(0.0f), Yaw(0.0f)
	{}

	XRotator(float InRoll, float InPitch, float InYaw)
		:Roll(InRoll), Pitch(InPitch), Yaw(InYaw)
	{}

	static const XRotator Zero;
};

class TTransform
{
public:
	TTransform()
	{
		Location = XVector3::Zero;
		Rotation = XRotator::Zero;
		Scale = XVector3::One;
	}

	XMatrix GetTransformMatrix() const
	{
		XMatrix S = XMatrix::CreateScale(Scale);
		XMatrix R = XMatrix::CreateFromYawPitchRoll(Rotation.Yaw * TMath::Pi / 180.0f, Rotation.Pitch * TMath::Pi / 180.0f, Rotation.Roll * TMath::Pi / 180.0f);
		XMatrix T = XMatrix::CreateTranslation(Location);

		return S * R * T;
	}

public:
	XVector3 Location;
	XRotator Rotation;
	XVector3 Scale;
};

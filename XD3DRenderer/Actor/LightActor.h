#pragma once

#include "Actor.h"

enum ELightType
{
	None,
	AmbientLight,
	DirectionalLight,
	PointLight,
	SpotLight,
	AreaLight
};

class XLightActor : public XActor
{
public:
	XLightActor(const std::string& Name, ELightType InType) 
		:XActor(Name), Type(InType)
	{

	}

	~XLightActor()
	{

	}

	ELightType GetType()
	{
		return Type;
	}

public:
	XVector3 GetLightColor() const
	{
		return Color;
	}

	virtual void SetLightColor(const XVector3& InColor)
	{
		Color = InColor;
	}

	float GetLightIntensity() const
	{
		return Intensity;
	}

	virtual void SetLightIntensity(float InIntensity)
	{
		Intensity = InIntensity;
	}



protected:
	ELightType Type = ELightType::None;

	XVector3 Color = XVector3::One;

	float Intensity = 10.0f;
};

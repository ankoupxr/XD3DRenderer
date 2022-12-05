#pragma once

#include "../Graphic/Transform.h"

class XComponent
{
public:
	XComponent() {}

	virtual ~XComponent() {}

public:
	virtual void SetWorldLocation(const XVector3& Location)
	{
		WorldTransform.Location = Location;
	}

	XVector3 GetWorldLocation() const
	{
		return WorldTransform.Location;
	}

	virtual void SetWorldRotation(const XRotator& Rotation)
	{
		WorldTransform.Rotation = Rotation;
	}

	XRotator GetWorldRotation() const
	{
		return WorldTransform.Rotation;
	}

	void SetWorldTransform(const XTransform& Transform)
	{
		WorldTransform = Transform;
	}

	XTransform GetWorldTransform() const
	{
		return WorldTransform;
	}

	void SetPrevWorldTransform(const XTransform& Transform)
	{
		PrevWorldTransform = Transform;
	}

	XTransform GetPrevWorldTransform() const
	{
		return PrevWorldTransform;
	}

protected:
	XTransform RelativeTransform; //TODO

	XTransform WorldTransform;

	XTransform PrevWorldTransform;
};

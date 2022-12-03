#pragma once

#include "../Graphic/Transform.h"

class XComponent
{
public:
	XComponent();
	virtual ~XComponent();

public:
	virtual void SetWorldLocation(const XVector3& Location)
	{
		WorldTransform.Location = Location;
	}

private:



protected:
	TTransform WorldTransform;

	TTransform PrevWorldTransform;
};



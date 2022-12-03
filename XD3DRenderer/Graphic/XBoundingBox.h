#pragma once

#include <DirectXCollision.h>
#include <vector>
#include "Transform.h"

class XBoundingBox
{
public:
	void Init(std::vector<XVector3> Points);

	//void Init(std::vector<XVertex> Vertices);

	XVector3 GetCenter() const { return (Min + Max) * 0.5f; }

	XVector3 GetExtend() const { return (Max - Min) * 0.5f; }

	XVector3 GetSize() const { return  (Max - Min); }

	int GetWidestAxis() const;

	float GetMaxWidth() const;

	float GetSurfaceArea() const;

	static XBoundingBox Union(const XBoundingBox& BoxA, const XBoundingBox& BoxB);

	static XBoundingBox Union(const XBoundingBox& Box, const XVector3& Point);

	XBoundingBox Transform(const TTransform& T);

	// If the ray¡¯s origin is inside the box, 0 is returned for Dist0
	//bool Intersect(const TRay& Ray, float& Dist0, float& Dist1);

	DirectX::BoundingBox GetD3DBox();

public:
	bool bInit = false;

	XVector3 Min = XVector3(TMath::Infinity);
	XVector3 Max = XVector3(-TMath::Infinity);
};
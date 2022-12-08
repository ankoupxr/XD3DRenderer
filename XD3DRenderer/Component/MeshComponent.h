#pragma once

#include <memory>
#include "Component.h"
#include <string>


class XMeshComponent : public XComponent
{
public:
	void SetMeshName(std::string InMeshName);

	std::string GetMeshName() const;

	bool IsMeshValid() const;

	bool GetLocalBoundingBox(XBoundingBox& OutBox);

	bool GetWorldBoundingBox(XBoundingBox& OutBox);

	void SetMaterialInstance(std::string MaterialInstanceName);

	XMaterialInstance* GetMaterialInstance() { return MaterialInstance; }

public:
	XMatrix TexTransform = XMatrix::Identity;

	// Flags
	bool bUseSDF = true;

private:
	std::string MeshName;

	XMaterialInstance* MaterialInstance;
};
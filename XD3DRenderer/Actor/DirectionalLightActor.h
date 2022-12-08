#pragma once

#include "LightActor.h"
#include "../Component/MeshComponent.h"

class XDirectionalLightActor : public XLightActor
{
public:
	XDirectionalLightActor(const std::string& Name);

	~XDirectionalLightActor();

public:
	virtual void SetActorTransform(const XTransform& NewTransform) override;

	XVector3 GetLightDirection() const;


private:
	void SetLightDirection(XRotator Rotation);

private:
	XVector3 Direction;

	XMeshComponent* MeshComponent = nullptr;
};
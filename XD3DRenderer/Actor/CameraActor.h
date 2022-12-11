#pragma once

#include "Actor.h"
#include "../Component/CameraComponent.h"

class XCameraActor : public XActor
{
public:
	XCameraActor(const std::string& Name);
	~XCameraActor();

	XCameraComponent* GetCameraComponent();

private:
	XCameraComponent* CameraComponent = nullptr;
};

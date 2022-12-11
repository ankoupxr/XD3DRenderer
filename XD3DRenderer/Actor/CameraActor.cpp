#include "CameraActor.h"

XCameraActor::XCameraActor(const std::string& Name)
	:XActor(Name)
{
	//CameraComponent
	CameraComponent = AddComponent<XCameraComponent>();

	RootComponent = CameraComponent;
}

XCameraActor::~XCameraActor()
{

}

XCameraComponent* XCameraActor::GetCameraComponent()
{
	return CameraComponent;
}
#include "DirectionalLightActor.h"

using namespace DirectX;

XDirectionalLightActor::XDirectionalLightActor(const std::string& Name)
	:XLightActor(Name, ELightType::DirectionalLight)
{
	MeshComponent = AddComponent<XMeshComponent>();

	RootComponent = MeshComponent;

	//Mesh
	MeshComponent->SetMeshName("CylinderMesh");

	//Material
	MeshComponent->SetMaterialInstance("DefaultMatInst");
}

XDirectionalLightActor::~XDirectionalLightActor()
{

}

void XDirectionalLightActor::SetActorTransform(const XTransform& NewTransform)
{
	XActor::SetActorTransform(NewTransform);

	SetLightDirection(NewTransform.Rotation);
}

void XDirectionalLightActor::SetLightDirection(XRotator Rotation)
{
	//Calculate Direction
	XMatrix R = XMatrix::CreateFromYawPitchRoll(Rotation.Yaw * TMath::Pi / 180.0f, Rotation.Pitch * TMath::Pi / 180.0f, Rotation.Roll * TMath::Pi / 180.0f);
	Direction = R.TransformNormal(XVector3::Up);
}

XVector3 XDirectionalLightActor::GetLightDirection() const
{
	return Direction;
}

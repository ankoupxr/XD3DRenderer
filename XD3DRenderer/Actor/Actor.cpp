#include "Actor.h"

XActor::XActor(const std::string& Name)
{
	SetName(Name);
}

void XActor::SetActorTransform(const XTransform& NewTransform)
{
	RootComponent->SetWorldTransform(NewTransform);
}

XTransform XActor::GetActorTransform() const
{
	return RootComponent->GetWorldTransform();
}

void XActor::SetActorLocation(const XVector3& NewLocation)
{
	RootComponent->SetWorldLocation(NewLocation);
}

XVector3 XActor::GetActorLocation() const
{
	return RootComponent->GetWorldLocation();
}

void XActor::SetActorRotation(const XRotator& NewRotation)
{
	RootComponent->SetWorldRotation(NewRotation);
}

XRotator XActor::GetActorRotation() const
{
	return RootComponent->GetWorldRotation();
}

void XActor::SetActorPrevTransform(const XTransform& PrevTransform)
{
	RootComponent->SetPrevWorldTransform(PrevTransform);
}

XTransform XActor::GetActorPrevTransform() const
{
	return RootComponent->GetPrevWorldTransform();
}
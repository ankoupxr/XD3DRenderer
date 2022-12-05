#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../Component/Component.h"
#include "../Graphic/Transform.h"


class XActor
{
public:
	XActor(const std::string& Name);

	virtual ~XActor() {}

public:
	virtual void Tick(float DeltaSeconds) {}

public:
	template<typename T>
	T* AddComponent()
	{
		auto NewComponent = std::make_unique<T>();
		T* Result = NewComponent.get();
		Components.push_back(std::move(NewComponent));

		return Result;
	}

	std::vector<XComponent*> GetComponets()
	{
		std::vector<XComponent*> Result;

		for (const auto& Component : Components)
		{
			Result.push_back(Component.get());
		}

		return Result;
	}

	template<typename T>
	std::vector<T*> GetComponentsOfClass()
	{
		std::vector<T*> Result;
		for (const auto& Component : Components)
		{
			T* ComponentOfClass = dynamic_cast<T*>(Component.get());
			if (ComponentOfClass)
			{
				Result.push_back(ComponentOfClass);
			}
		}

		return Result;
	}

	XComponent* GetRootComponent() const
	{
		return RootComponent;
	}

	virtual void SetActorTransform(const XTransform& NewTransform);

	XTransform GetActorTransform() const;

	void SetActorLocation(const XVector3& NewLocation);

	XVector3 GetActorLocation() const;

	void SetActorRotation(const XRotator& NewRotation);

	XRotator GetActorRotation() const;

	void SetActorPrevTransform(const XTransform& PrevTransform);

	XTransform GetActorPrevTransform() const;

	void SetName(std::string Name) { ActorName = Name; }

	std::string GetName() const { return ActorName; }

protected:
	std::string ActorName;

	std::vector<std::unique_ptr<XComponent>> Components;

	XComponent* RootComponent = nullptr;
};


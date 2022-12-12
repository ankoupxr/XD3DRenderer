#pragma once

#include "GameTimer.h"
#include "../Graphic/Color.h"

class System;

class XWorld
{
public:
	XWorld();
	virtual ~XWorld();
	virtual void InitWorld(System* sys);
	virtual void Update(const GameTimer& gt);
	virtual void EndFrame(const GameTimer& gt);

	template<typename T>
	T* AddActor(const std::string& Name)
	{
		auto NewActor = std::make_unique<T>(Name);
		T* Result = NewActor.get();
		Actors.push_back(std::move(NewActor));

		return Result;
	}

	std::vector<XActor*> GetActors()
	{
		std::vector<XActor*> Result;

		for (const auto& Actor : Actors)
		{
			Result.push_back(Actor.get());
		}

		return Result;
	}

	template<typename T>
	std::vector<T*> GetAllActorsOfClass()
	{
		std::vector<T*> Result;
		for (const auto& Actor : Actors)
		{
			T* ActorOfClass = dynamic_cast<T*>(Actor.get());
			if (ActorOfClass)
			{
				Result.push_back(ActorOfClass);
			}
		}

		return Result;
	}

	XCameraComponent* GetCameraComponent() { return CameraComponent; }


public:
	void DrawPoint(const XVector3& PointInWorld, const XColor& Color, int Size = 0);

	//void DrawPoint(const Point& Point);

	//const std::vector<TPoint>& GetPoints();

	void DrawLine(const XVector3& PointAInWorld, const XVector3& PointBInWorld, const XColor& Color);

	//void DrawLine(const XLine& Line);

	//const std::vector<TLine>& GetLines();

	void DrawBox3D(const XVector3& MinPointInWorld, const XVector3& MaxPointInWorld, const XColor& Color);

	void DrawTriangle(const XVector3& PointAInWorld, const XVector3& PointBInWorld, const XVector3& PointCInWorld, const XColor& Color);

	//void DrawTriangle(const XTriangle& Triangle);

	//const std::vector<TTriangle>& GetTriangles();

	//void DrawSprite(const std::string& TextureName, const UIntPoint& TextureSize, const RECT& SourceRect, const RECT& DestRect);

	//const std::vector<XSprite>& GetSprites();

	void DrawString(int ID, std::string Str, float Duration = 1.0f);

	//void GetTexts(std::vector<TText>& OutTexts);

protected:
	std::vector<std::unique_ptr<XActor>> Actors;

	//std::vector<XPoint> Points;

	//std::vector<XLine> Lines;

	//std::vector<TTriangle> Triangles;

	//std::vector<TSprite> Sprites;

	//TTextManager TextManager;

protected:
	System* Engine = nullptr;

	HWND  MainWindowHandle = nullptr; // main window handle

	XCameraComponent* CameraComponent = nullptr;

	float MoveSpeed = 2.0f;

private:
	POINT LastMousePos;

	bool bKey_H_Pressed = false;

	bool bKey_J_Pressed = false;

	bool bKey_K_Pressed = false;

	bool bKey_L_Pressed = false;

};

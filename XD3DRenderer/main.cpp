#include <windows.h>
#include "System/System.h"
#include "Actor/MeshActor.h"
#include "Actor/CameraActor.h"
#include "Actor/DirectionalLightActor.h"
#include "Actor/PointLightActor.h"
#include "Actor/SpotLightActor.h"
#include "Actor/AreaLightActor.h"

class PBRWorld : public XWorld
{
public:
	PBRWorld() {}

	~PBRWorld() {}

	virtual void InitWorld(System* InEngine) override
	{
		//³õÊ¼»¯ÉãÏñ»ú
		auto Camera = AddActor<XCameraActor>("Camera");
		CameraComponent = Camera->GetCameraComponent();
		CameraComponent->SetWorldLocation(XVector3(0.55f, 1.50f, -3.84f));
		CameraComponent->RotateY(-120.0f);
		CameraComponent->UpdateViewMatrix();
	}
};


#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		{
			//_CrtSetBreakAlloc(550388);

			PBRWorld* World = new PBRWorld();

			//TRenderSettings RenderSettings;

			System Engine(hInstance);
			//if (!Engine.Initialize(World, RenderSettings))
				return 0;

			Engine.Run();

			Engine.Destroy();
		}

		return 0;
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}
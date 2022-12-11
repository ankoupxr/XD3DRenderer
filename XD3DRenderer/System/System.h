#pragma once

#include "GameTimer.h"
#include "XWorld.h"
#include "../PlatForm/D3D12/D3D12RHI.h"

class  System
{
public:
	 System(HINSTANCE HInstance);

     System(const System& rhs) = delete;

     System& operator=(const System& rhs) = delete;

     virtual ~System();

public:
    static System* GetEngineSingleton();

    HINSTANCE GetEngineInstHandle()const;
    HWND GetMainWnd()const;

    bool Initialize();

    int Run();

    bool Destroy();

    LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    int GetWindowWidth() { return WindowWidth; }

    int GetWindowHeight() { return WindowHeight; }



private:

    bool InitMainWindow();

    void OnResize();

    void CalculateFrameStats();


protected:
    void Update(const GameTimer& gt);

    void EndFrame(const GameTimer& gt);

    // Convenience overrides for handling mouse input.
    void OnMouseDown(WPARAM btnState, int x, int y) { World->OnMouseDown(btnState, x, y); }
    void OnMouseUp(WPARAM btnState, int x, int y) { World->OnMouseUp(btnState, x, y); }
    void OnMouseMove(WPARAM btnState, int x, int y) { World->OnMouseMove(btnState, x, y); }
    void OnMouseWheel(float WheelDistance) { World->OnMouseWheel(WheelDistance); }

protected:
    static System* EngineSingleton;
    std::wstring WindowTile = L"XD3DRenderer";

    bool bInitialize = false;

    HINSTANCE EngineInstHandle = nullptr; // application instance handle
    HWND      MainWindowHandle = nullptr; // main window handle
    bool      bAppPaused = false;  // is the application paused?
    bool      bAppMinimized = false;  // is the application minimized?
    bool      bAppMaximized = false;  // is the application maximized?
    bool      bResizing = false;   // are the resize bars being dragged?
    bool      bFullscreenState = false;// fullscreen enabled

    int WindowWidth = 1280;
    int WindowHeight = 720;

    GameTimer Timer;

    std::unique_ptr<D3D12RHI> D3D12RHI;
};


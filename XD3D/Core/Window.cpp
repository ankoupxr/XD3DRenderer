#include "stdafx.h"
#include "Window.h"
#include "imgui_impl_win32.h"
#include <winuser.h>


Window::Window(uint32 width, uint32 height)
{
    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASS wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandleA(0);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpfnWndProc = WndProcStatic;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	check(RegisterClassExA(&wc));

    	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	RECT windowRect = { 0, 0, (LONG)width, (LONG)height };
	AdjustWindowRect(&windowRect, windowStyle, false);

	int x = (displayDimensions.x - width) / 2;
	int y = (displayDimensions.y - height) / 2;

	m_Window = CreateWindowExA(
		0,
		WINDOW_CLASS_NAME,
		"",
		windowStyle,
		x,
		y,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		GetModuleHandleA(nullptr),
		this
	);
	check(m_Window);

	ShowWindow(m_Window, SW_SHOWDEFAULT);
	UpdateWindow(m_Window);
}

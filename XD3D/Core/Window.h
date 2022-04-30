#pragma once

class Window
{
public:
	static constexpr const char* WINDOW_CLASS_NAME = "WndClass";
	Window(uint32 width, uint32 height);

	~Window();

};

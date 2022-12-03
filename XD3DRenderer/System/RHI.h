#pragma once
#include <Windows.h>

class RHI
{
public:
	virtual ~RHI();
	virtual void Initialize(HWND WindowHandle, int WindowWidth, int WindowHeight) = 0;
	virtual void Destroy() = 0;

private:

};

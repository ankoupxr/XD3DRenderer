#pragma once

#include "GameTimer.h"

class System;

class XWorld
{
public:
	XWorld();
	virtual ~XWorld();
	virtual void InitWorld(System* sys);
	virtual void Update(const GameTimer& gt);
	virtual void EndFrame(const GameTimer& gt);



private:

};

#pragma once

#include <string>
#include <filesystem>
#include "Convert.h"

class TFileHelpers
{
public:
	static bool IsFileExit(const std::wstring& FileName)
	{
		//return std::filesystem::exists(FileName);
		return true;
	}

	static std::wstring EngineDir()
	{
		std::wstring EngineDir = Convert::StrToWStr("")) + L"Engine/";

		return EngineDir;
	}
};

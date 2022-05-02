require "vstudio"

ENGINE_NAME = "XD3D"
ROOT = "../"
SOURCE_DIR = ROOT .. ENGINE_NAME .. "/"
WIN_SDK = "10.0.19041.0"

-- Address Sanitizer API

premake.api.register{
	name="enableASAN",
	scope="config",
	kind="string",
	allowed={"true", "false"}
}

premake.override(premake.vstudio.vc2010, "configurationProperties", function(base, cfg)
	local m = premake.vstudio.vc2010
	m.propertyGroup(cfg, "Configuration")
	premake.callArray(m.elements.configurationProperties, cfg)
	if cfg.enableASAN then
	   m.element("EnableASAN", nil, cfg.enableASAN)
	end
	premake.pop('</PropertyGroup>')
end)

function runtimeDependency(source, destination)
	postbuildcommands { ("{COPY} \"$(SolutionDir)Lib/" .. source .. "\" \"$(OutDir)" .. destination .. "/\"") }
end

workspace (ENGINE_NAME)
	basedir (ROOT)
	configurations { "Debug", "Release", "DebugASAN" }
    platforms { "x64" }
	defines { "x64" }
	language "C++"
	cppdialect "c++17"
	startproject (ENGINE_NAME)
	symbols "On"
	architecture "x64"
	characterset "MBCS"
	flags {"MultiProcessorCompile", "ShadowedVariables", "FatalWarnings"}
	rtti "Off"
	warnings "Extra"
	justmycode "Off"
	editAndContinue "Off"
	system "windows"
	conformancemode "On"
	defines { "PLATFORM_WINDOWS=1", "WIN32" }
	targetdir (ROOT .. "Build/$(ProjectName)_$(Platform)_$(Configuration)")
	objdir (ROOT .. "Build/Intermediate/$(ProjectName)_$(Platform)_$(Configuration)")

	--Unreferenced variable
	disablewarnings {"4100"}
	
	filter "configurations:Debug"
 		runtime "Debug"
		defines { "_DEBUG" }
		optimize ("Off")
		--inlining "Explicit"

	filter "configurations:Release"
 		runtime "Release"
		defines { "RELEASE" }
		optimize ("Full")
		flags { "NoIncrementalLink" }

	filter "configurations:DebugASAN"
 		runtime "Debug"
		defines { "_DEBUG" }
		optimize ("Off")
		flags{ "NoRuntimeChecks", "NoIncrementalLink"}
		enableASAN "true"

	filter {}

	project (ENGINE_NAME)
		location (ROOT .. ENGINE_NAME)
		pchheader ("stdafx.h")
		pchsource (ROOT .. ENGINE_NAME .. "/stdafx.cpp")
		systemversion (WIN_SDK)
		kind "WindowedApp"

		includedirs { "$(ProjectDir)" }

		for i, dir in pairs(os.matchdirs(SOURCE_DIR .. "Lib/*")) do
			dirname = string.explode(dir, "/")
			dir = dirname[#dirname]
			includedirs ("$(ProjectDir)Lib/" .. dir)
		end

		files
		{ 
			(SOURCE_DIR .. "**.h"),
			(SOURCE_DIR .. "**.hpp"),
			(SOURCE_DIR .. "**.cpp"),
			(SOURCE_DIR .. "**.inl"),
			(SOURCE_DIR .. "**.c"),
			(SOURCE_DIR .. "**.natvis"),
			(SOURCE_DIR .. "**.editorconfig"),
		}

		filter ("files:" .. SOURCE_DIR .. "Lib/**")
			flags { "NoPCH" }
			removeflags "FatalWarnings"
			warnings "Default"
		filter {}

		-- XD3D
		includedirs "$(SolutionDir)Libraries/XD3D/include"
		runtimeDependency("XD3D/bin/XD3DCore.dll", "XD3D")
		runtimeDependency("XD3D/bin/XD3DSDKLayers.dll", "XD3D")
		links {	"XD3D.lib", "dxgi" }

		-- Pix
		includedirs "$(SolutionDir)Libraries/Pix/include"
		libdirs "$(SolutionDir)Libraries/Pix/lib"
		runtimeDependency("Pix/bin/WinPixEventRuntime.dll", "")
		links { "WinPixEventRuntime" }

		-- DXC
		includedirs "$(SolutionDir)Libraries/Dxc/include"
		runtimeDependency ("Dxc/bin/dxcompiler.dll", "")
		runtimeDependency ("Dxc/bin/dxil.dll", "")

		-- DirectXMath
		includedirs "$(SolutionDir)Libraries/DirectXMath/include"


newaction {
	trigger     = "clean",
	description = "Remove all binaries and generated files",

	execute = function()
		os.rmdir("../Build")
		os.rmdir("../ipch")
		os.rmdir("../.vs")
		os.remove("../*.sln")
		os.remove(SOURCE_DIR .. "*.vcxproj.*")
	end
}
			
--------------------------------------------------------
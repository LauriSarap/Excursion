workspace "BrainGrid"
	architecture "x64"
	startproject "DigitDetection"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}

project "BrainGridLibrary"
	location "BrainGridLibrary"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bgpch.h"
	pchsource "BrainGridLibrary/src/bgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"BG_PLATFORM_WINDOWS",
			"BG_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/DigitDetection/\"")
		}

	filter "configurations:Debug"
		defines "BG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BG_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "BG_DISTRIBUTION"
		runtime "Release"
		optimize "On"

project "DigitDetection"
	location "DigitDetection"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
        "BrainGridLibrary/src"
	}

	links
	{
		"BrainGridLibrary"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"BG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "HZ_DISTRIBUTION"
		runtime "Release"
		optimize "On"
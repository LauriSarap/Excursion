workspace "Excursion"
	architecture "x64"
	startproject "MNIST"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}

project "ExcursionLibrary"
	location "ExcursionLibrary"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bgpch.h"
	pchsource "ExcursionLibrary/src/bgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"libs/eigen/Eigen"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"EX_PLATFORM_WINDOWS",
			"EX_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/XORProblem/\"")
		}

	filter "configurations:Debug"
		defines "EX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "EX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "EX_DISTRIBUTION"
		runtime "Release"
		optimize "On"

project "XORProblem"
	location "Examples/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Examples/%{prj.name}/**.h",
		"Examples/%{prj.name}/**.cpp"
	}

	includedirs
	{
        "ExcursionLibrary/src",
        "libs/eigen/Eigen"
	}

	links
	{
		"ExcursionLibrary"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"EX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "EX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "EX_DISTRIBUTION"
		runtime "Release"
		optimize "On"

project "MNIST"
	location "Examples/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Examples/%{prj.name}/**.h",
		"Examples/%{prj.name}/**.cpp"
	}

	includedirs
	{
        "ExcursionLibrary/src",
        "libs/eigen/Eigen"
	}

	links
	{
		"ExcursionLibrary"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"EX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "EX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "EX_DISTRIBUTION"
		runtime "Release"
		optimize "On"
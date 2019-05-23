workspace "VinoGL"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "VinoGL/vendor/GLFW/include"
IncludeDir["VinoGL"] = "VinoGL/src"
IncludeDir["spdlog"] = "VinoGL/vendor/spdlog/include"
-- Include premake file to create GLFW project
include "VinoGL/vendor/GLFW"

project "VinoGL"
	location "VinoGL"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "vnpch.h"
	pchsource "VinoGL/src/vnpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.VinoGL}",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"VN_PLATFORM_WINDOWS",
			"VN_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Tests")
		}

	filter "configurations:Debug"
		defines { "VN_DEBUG", "VN_ENABLE_ASSERTS" }
		symbols "On"

	filter "configurations:Release"
		defines "VN_RELEASE"
		optimize "On"

	filter "configurations:DIST"
		defines "VN_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.VinoGL}"
	}

	links
	{
		"VinoGL"
	}

	defines "VN_ENTRY_POINT"

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"VN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VN_RELEASE"
		optimize "On"

	filter "configurations:DIST"
		defines "VN_DIST"
		optimize "On"

project "Tests"
	location "Tests"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"%{prj.name}/vendor/catch/include",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.VinoGL}"
	}

	links
	{
		"VinoGL"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"VN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VN_RELEASE"
		optimize "On"

	filter "configurations:DIST"
		defines "VN_DIST"
		optimize "On"
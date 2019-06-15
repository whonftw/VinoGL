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
IncludeDir["Glad"] = "VinoGL/vendor/Glad/include"
-- Include premake file to create GLFW project
include "VinoGL/vendor/GLFW"
include "VinoGL/vendor/Glad"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"VN_PLATFORM_WINDOWS",
			"VN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Tests")
		}

	filter "configurations:Debug"
		defines { "VN_DEBUG", "VN_ENABLE_ASSERTS" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "VN_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:DIST"
		runtime "Release"
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
		systemversion "latest"

		defines
		{
			"VN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VN_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "VN_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:DIST"
		defines "VN_DIST"
		runtime "Release"
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
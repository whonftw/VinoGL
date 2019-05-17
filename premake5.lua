workspace "VinoGL"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "VinoGL"
	location "Projects/VinoGL"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Projects/%{prj.name}/src/**.h",
		"Projects/%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Projects/${prj.name}/vendor/spdlog/include"
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
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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

project "Sandbox"
	location "Projects/Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Projects/%{prj.name}/src/**.h",
		"Projects/%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Projects/VinoGL/vendor/spdlog/include",
		"Projects/VinoGL/src"
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
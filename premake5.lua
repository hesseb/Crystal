workspace "Crystal"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] 		= "Crystal/vendor/GLFW/include"
	IncludeDir["Glad"] 		= "Crystal/vendor/Glad/include"
	IncludeDir["ImGui"] 	= "Crystal/vendor/imgui"
	IncludeDir["spdlog"] 	= "Crystal/vendor/spdlog/include/"
	IncludeDir["glm"] 		= "Crystal/vendor/glm"

group "Dependencies"
	include "Crystal/vendor/GLFW"
	include "Crystal/vendor/Glad"
	include "Crystal/vendor/imgui"

group ""

project "Crystal"
	location "Crystal"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "crpch.h"
	pchsource "Crystal/src/crpch.cpp"

	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src/",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CR_PLATFORM_WINDOWS",
			"CR_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "CR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CR_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Crystal/src/",
		"Crystal/vendor",
		"Crystal/vendor/spdlog/include/",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Crystal"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CR_DIST"
		runtime "Release"
		optimize "on"
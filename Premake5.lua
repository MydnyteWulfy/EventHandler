workspace "EventerWorkspace"
	architecture "x64"
	configurations {"Debug", "Release", "Dist"}
	
-- Locals --
outputdir = "%{cfg.buildcfg}-%{cfg.system}%{cfg.architecture}"

-- Eventer DLL --
project "Eventer"

	location "Eventer"
	
	kind "SharedLib"
	language "C++"
	
	targetdir ("out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("out/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"SYSTEM_WINDOWS",
			"SYSTEM_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../out/bin/" .. outputdir .. "/TestingApp")
		}
		
	filter "configurations:Debug"
		defines
		{
			"DEBUG",
			"SYSTEM_TRY_ENABLE_LOGGING",
			"SYSTEM_DEFAULT_ERROR_LEVEL_INFO"
		}
		
		optimize "Debug"
		
	filter "configurations:Release"
		defines
		{
			"NDEBUG",
			"RELEASE",
			"SYSTEM_TRY_ENABLE_LOGGING",
			"SYSTEM_DEFAULT_ERROR_LEVEL_ERROR"
		}
		
		optimize "On"
		
	filter "configurations:Dist"
		defines
		{
			"NDEBUG",
			"DIST"
		}
		
		optimize "On"

	
-- Testing app --	
project "TestingApp"

	location "TestingApp"
	
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("out/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Eventer/Src"
	}
	
	links
	{
		"Eventer"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"SYSTEM_WINDOWS"
		}
		
		
	filter "configurations:Debug"
		defines
		{
			"DEBUG",
			"SYSTEM_TRY_ENABLE_LOGGING",
			"SYSTEM_DEFAULT_ERROR_LEVEL_INFO"
		}
		
		optimize "Debug"
		
	filter "configurations:Release"
		defines
		{
			"NDEBUG",
			"RELEASE",
			"SYSTEM_TRY_ENABLE_LOGGING",
			"SYSTEM_DEFAULT_ERROR_LEVEL_ERROR"
		}
		
		optimize "On"
		
	filter "configurations:Dist"
		defines
		{
			"NDEBUG",
			"DIST"
		}
		
		optimize "On"
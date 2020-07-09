workspace "CTXEngineEntityComponentSystem"
	architecture "x64"
	startproject "CTXEngineECS"

	configurations
	{
		"Debug", "Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directiories for libs --
IncludeDir = {} 

group "Libraries"

group ""

group "Graphics"

group ""

project "CTXEngineECS"
	location "CTXEngineECS"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("Build/bin/" .. outputdir .. "/%{prj.name}/lib")   --bin
	objdir ("Build/bin/" .. outputdir .. "/%{prj.name}/obj")  -- bin-obj

	files
	{
		"%{prj.name}/Sources/**.h",
		"%{prj.name}/Sources/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/Sources",
	}

	links
	{
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CTX_PLATFORM_WINDOWS",
			"CTX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		-- Now we use the static lib (.lib) instead dynamic lib (.dll)
		-- and it don't need to copy and paste the dll file. But i keep
		-- it here for while, maybe in future im delete this.

		--postbuildcommands
		--{
		--	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Craftix/\"")
		--}

	filter "configurations:Debug"
		defines "CTX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CTX_RELEASE"
		runtime "Release"
		optimize "on"
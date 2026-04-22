workspace "Boneware"
	configurations { "Debug", "Release" }
    architecture "x86_64"
	language "C++"
	cppdialect "C++20"
	defines { "_CRT_SECURE_NO_WARNINGS", "NOMINMAX" } 
	filter "system:windows"
		usestandardpreprocessor "On"
	filter{}

project "Boneware"
	kind "SharedLib"
	
	pchheader "pch.hpp"
    pchsource "src/pch.cpp"
	
	includedirs { "src", "deps/**" }
	files { 
		"deps/**.hpp", 
		"deps/**.h", 
		"src/**.hpp",
		"src/**.h",
		"src/**.cpp" 
	}
	
	forceincludes { "pch.hpp" } 
	
	targetdir "build/bin/%{cfg.buildcfg}"
	objdir    "build/%{cfg.buildcfg}"
	
	filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Full"
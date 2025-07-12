workspace "Browser-Renderer"
    architecture "x64"
    startproject "browser-renderer"

    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["WINDOWING"] = "../vendor/WINDOWING/include"

LibDir = {}
LibDir["WINDOWING"] = "../vendor/WINDOWING/lib"



group "browser-renderer"
    include "browser-renderer/browser-renderer.lua"
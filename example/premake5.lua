workspace "Web-Engine-Example"
    architecture "x64"
    startproject "Web-Engine-Example"
    configurations { "debug", "release" }

    targetdir("%{wks.location}/export/%{cfg.system}/%{cfg.buildcfg}/libs/%{prj.name}")
    objdir("%{wks.location}/export/%{cfg.system}/%{cfg.buildcfg}/objs/%{prj.name}")

    defines
    {
        "GLM_ENABLE_EXPERIMENTAL",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
        "GLM_FORCE_LEFT_HANDED"
    }

project "Web-Engine-Example"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir("%{wks.location}/export/%{cfg.system}/%{cfg.buildcfg}/bin")

    files { "src/**.h", "src/**.c", "src/**.hpp", "src/**.cpp" }

    includedirs
    {
        "src",
        "../src",
        "../vendor/glfw/glfw/include",
        "../vendor/glm/glm",
        "../vendor/webgpu/include",
        "../vendor/glfw3webgpu",
        "../vendor/stb_image",
        "../vendor/imgui", -- i like this one better
        "../vendor/imgui/imgui" -- im required to do this
    }

    links
    {
        "Web-Engine"
    }

    filter "configurations:debug"
        defines { "WE_DEBUG" }
        runtime "Debug"
        optimize "Off"
        symbols "On"

    filter "configurations:release"
        defines { "WE_RELEASE" }
        runtime "Release"
        optimize "Full"
        symbols "Off"

    filter "system:windows"
		defines { "WE_WINDOWS" }

	filter "system:linux"
		defines { "WE_LINUX" }

    filter {}

group "Dependencies"
    include "../"
group ""

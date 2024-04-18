include "vendor/glfw"
include "vendor/glfw3webgpu"
include "vendor/imgui"

project "Web-Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files { "src/**.h", "src/**.c", "src/**.hpp", "src/**.cpp" }

    defines
    {
        "GLM_ENABLE_EXPERIMENTAL",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
        "GLM_FORCE_LEFT_HANDED"
    }

    includedirs
    {
        "src",
        "vendor/glfw/glfw/include",
        "vendor/glm/glm",
        "vendor/webgpu/include",
        "vendor/glfw3webgpu",
        "vendor/stb_image",
        "vendor/imgui", -- i like this one better
        "vendor/imgui/imgui" -- im required to do this
    }

    links
    {
        "GLFW",
        "GLFW3WebGPU",
        "ImGui"
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

    filter "system:windows"
        links { "%{prj.location}/vendor/webgpu/bin/windows-%{cfg.architecture}/wgpu_native.dll.lib" }

    filter "system:linux"
        libdirs { "%{prj.location}/vendor/webgpu/bin/linux-%{cfg.architecture}" }
        links { "wgpu_native" }

    filter "system:windows"
        postbuildcommands
        {
            "{COPY} \"%{prj.location}/vendor/webgpu/bin/windows-%{cfg.architecture}/wgpu_native.dll\" \""..ExeDir.."/\"",
        }

    filter "system:linux"
        local current_directory = os.getcwd()
        local absWksPath = current_directory:match("(.+)%/[^%/]+$")

        postbuildcommands
        {
            "{COPY} \""..absWksPath.."/vendor/webgpu/bin/linux-%{cfg.architecture}/libwgpu_native.so\" \""..ExeDir.."/\"",
        }

    filter {}

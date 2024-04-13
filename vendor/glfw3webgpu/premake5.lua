project "GLFW3WebGPU"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files { "**.h", "**.c", "**.hpp", "**.cpp" }

    includedirs
    {
        "%{prj.location}/../glfw/glfw/include",
        "%{prj.location}/../webgpu/include",
    }

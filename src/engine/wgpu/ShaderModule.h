#pragma once

#include <webgpu/webgpu.hpp>
#include <string>

class ShaderModule 
{
public:
    ShaderModule(std::string_view shaderSource);
    ~ShaderModule();

    wgpu::ShaderModule GetShaderModule() const { return _shaderModule; }
    operator wgpu::ShaderModule() const { return _shaderModule; }
private:
    wgpu::ShaderModule _shaderModule = nullptr;
};

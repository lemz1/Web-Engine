#pragma once

#include <webgpu/webgpu.hpp>
#include "engine/util/Types.h"
#include "engine/wgpu/ShaderModule.h"
#include "engine/wgpu/Buffer.h"

class RenderPipeline 
{
public:
    RenderPipeline(
        std::string_view shaderSource,
        const Vector<wgpu::VertexBufferLayout>& vertexBufferLayouts,
        const Vector<wgpu::BindGroupLayoutEntry>& bindGroupLayoutEntries
    );
    ~RenderPipeline();

    const Scoped<ShaderModule>& GetShaderModule() const { return _shaderModule; }
    wgpu::BindGroupLayout GetBindGroupLayout() const { return _bindGroupLayout; }
    wgpu::PipelineLayout GetPipelineLayout() const { return _pipelineLayout; }
    
    wgpu::RenderPipeline GetPipeline() const { return _pipeline; }
    operator wgpu::RenderPipeline() const { return _pipeline; }
    operator WGPURenderPipeline() const { return _pipeline; }
private:
    Scoped<ShaderModule> _shaderModule = nullptr;
    wgpu::BindGroupLayout _bindGroupLayout = nullptr;
    wgpu::PipelineLayout _pipelineLayout = nullptr;
    wgpu::RenderPipeline _pipeline = nullptr;
};

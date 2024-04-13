#pragma once

#include <webgpu/webgpu.hpp>
#include "engine/util/Types.h"
#include "engine/wgpu/ShaderModule.h"

class RenderPipeline 
{
public:
    RenderPipeline(
        std::string_view vertexSource,
        std::string_view fragmentSource,
        const Vector<wgpu::VertexBufferLayout>& vertexBufferLayouts
    );
    ~RenderPipeline();

    const Scoped<ShaderModule>& GetVertexModule() const { return _vertexModule; }
    const Scoped<ShaderModule>& GetFragmentModule() const { return _fragmentModule; }
    wgpu::PipelineLayout GetPipelineLayout() const { return _pipelineLayout; }
    
    wgpu::RenderPipeline GetPipeline() const { return _pipeline; }
    operator wgpu::RenderPipeline() const { return _pipeline; }
private:
    Scoped<ShaderModule> _vertexModule = nullptr;
    Scoped<ShaderModule> _fragmentModule = nullptr;
    wgpu::PipelineLayout _pipelineLayout = nullptr;
    wgpu::RenderPipeline _pipeline = nullptr;
};

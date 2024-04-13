#include "ShaderModule.h"

#include "engine/core/Application.h"

ShaderModule::ShaderModule(std::string_view shaderSource)
{
    wgpu::Device device = Application::GetWGPUContext()->device;

    wgpu::ShaderModuleWGSLDescriptor shaderCodeDesc;
    shaderCodeDesc.chain.next = nullptr;
    shaderCodeDesc.chain.sType = wgpu::SType::ShaderModuleWGSLDescriptor;
    shaderCodeDesc.code = shaderSource.data();

    wgpu::ShaderModuleDescriptor shaderDesc;
    shaderDesc.nextInChain = &shaderCodeDesc.chain;
    shaderDesc.hintCount = 0;
    shaderDesc.hints = nullptr;
    
    _shaderModule = device.createShaderModule(shaderDesc);
}

ShaderModule::~ShaderModule()
{
    _shaderModule.release();
}

#include "Sampler.h"

#include "engine/core/Application.h"

Sampler::Sampler(
    wgpu::AddressMode addressMode,
    wgpu::FilterMode filterMode
)
{
    wgpu::Device device = Application::GetWGPUContext()->device;

    wgpu::SamplerDescriptor samplerDesc = wgpu::Default;
    samplerDesc.addressModeU = addressMode;
    samplerDesc.addressModeV = addressMode;
    samplerDesc.addressModeW = addressMode;
    samplerDesc.magFilter = filterMode;
    samplerDesc.minFilter = filterMode;
    samplerDesc.mipmapFilter = wgpu::MipmapFilterMode::Linear;
    samplerDesc.lodMinClamp = 0.0f;
    samplerDesc.lodMaxClamp = 1.0f;
    samplerDesc.compare = wgpu::CompareFunction::Undefined;
    samplerDesc.maxAnisotropy = 1;
    _sampler = device.createSampler(samplerDesc);
}

Sampler::~Sampler()
{
	_sampler.release();
}

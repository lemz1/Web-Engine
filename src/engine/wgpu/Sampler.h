#pragma once

#include <webgpu/webgpu.hpp>

class Sampler
{
public:
	Sampler(
		wgpu::AddressMode addressMode = wgpu::AddressMode::ClampToEdge,
		wgpu::FilterMode filterMode = wgpu::FilterMode::Linear
	);
	~Sampler();

	wgpu::Sampler GetSampler() const { return _sampler; }
	operator wgpu::Sampler() const { return _sampler; }
	operator WGPUSampler() const { return _sampler; }
private:
	wgpu::Sampler _sampler = nullptr;
};

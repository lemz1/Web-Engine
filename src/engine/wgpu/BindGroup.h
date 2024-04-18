#pragma once

#include <webgpu/webgpu.hpp>
#include "engine/util/Types.h"

class BindGroup
{
public:
	BindGroup(
		const Vector<wgpu::BindGroupEntry>& bindGroupEntries,
		wgpu::BindGroupLayout bindGroupLayout
	);
	~BindGroup();

	wgpu::BindGroup GetBindGroup() const { return _bindGroup; }
	operator wgpu::BindGroup() const { return _bindGroup; }
	operator WGPUBindGroup() const { return _bindGroup; }
private:
	wgpu::BindGroup _bindGroup = nullptr;
};

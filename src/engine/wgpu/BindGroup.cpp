#include "BindGroup.h"

#include "engine/core/Application.h"

BindGroup::BindGroup(
	const Vector<wgpu::BindGroupEntry>& bindGroupEntries,
	wgpu::BindGroupLayout bindGroupLayout
)
{
	wgpu::Device device = Application::GetWGPUContext()->device;

	wgpu::BindGroupDescriptor bindGroupDesc = wgpu::Default;
	bindGroupDesc.entryCount = (uint32_t)bindGroupEntries.size();
	bindGroupDesc.entries = bindGroupEntries.data();
	bindGroupDesc.layout = bindGroupLayout;

	_bindGroup = device.createBindGroup(bindGroupDesc);
}

BindGroup::~BindGroup()
{
	_bindGroup.release();
}

#pragma once

#include <webgpu/webgpu.hpp>

#include "engine/core/event/Event.h"

class State
{
public:
	State() = default;
	virtual ~State() = default;

	virtual void Create() {}
	virtual void Event(const Event& event) {}
	virtual void Update(float deltaTime) {}
	virtual void Draw(wgpu::RenderPassEncoder renderPass) {}
	virtual void DrawImGui() {}
	virtual void Destroy() {}
};

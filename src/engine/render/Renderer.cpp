#include "Renderer.h"

#include <string>
#include <algorithm>

Vector<DrawGroup> Renderer::_DrawGroups = {};

std::string Renderer::_DefaultVertexSource = R"(
struct VertexInput {
    @location(0) position: vec2<f32>,
    @location(1) texCoord: vec2<f32>,
};

struct VertexOutput {
    @builtin(position) clipPosition: vec4<f32>,
    @location(0) texCoord: vec2<f32>,
};

struct UniformData {
    modelViewProjection: mat4x4<f32>, 
    tint: vec4<f32>,
};

@group(0) @binding(0) var textureSampler: sampler;
@group(0) @binding(1) var texture: texture_2d<f32>;
@group(0) @binding(2) var<uniform> uniformData: UniformData;

@vertex
fn vsMain(in: VertexInput) -> VertexOutput {
    var out: VertexOutput;

    out.clipPosition = uniformData.modelViewProjection * vec4<f32>(in.position, 0.0, 1.0);
    out.texCoord = in.texCoord;
    return out;
}
)";

std::string Renderer::_DefaultFragmentSource = R"(
@fragment
fn fsMain(in: VertexOutput) -> @location(0) vec4<f32> {
	var color: vec4<f32> = textureSample(texture, textureSampler, in.texCoord);
    color *= uniformData.tint;
	let gammaCorrectedColor: vec4<f32> = vec4<f32>(pow(color.rgb, vec3<f32>(2.2)), color.a);
	return gammaCorrectedColor;
}
)";

Ref<RenderPipeline> Renderer::_DefaultRenderPipeline = nullptr;

void Renderer::Init()
{
    Vector<wgpu::VertexAttribute> vertexAttributes(2, wgpu::Default);
    {
        wgpu::VertexAttribute& vertexAttribute = vertexAttributes[0];
        vertexAttribute.shaderLocation = 0;
        vertexAttribute.offset = 0;
        vertexAttribute.format = wgpu::VertexFormat::Float32x2;
    }
    {
        wgpu::VertexAttribute& vertexAttribute = vertexAttributes[1];
        vertexAttribute.shaderLocation = 1;
        vertexAttribute.offset = 0;
        vertexAttribute.format = wgpu::VertexFormat::Float32x2;
    }

    Vector<wgpu::VertexBufferLayout> vertexBufferLayouts(2, wgpu::Default);
    {
        wgpu::VertexBufferLayout& vertexBufferLayout = vertexBufferLayouts[0];
        vertexBufferLayout.attributeCount = 1;
        vertexBufferLayout.attributes = &vertexAttributes[0];
        vertexBufferLayout.arrayStride = sizeof(Vec2);
        vertexBufferLayout.stepMode = wgpu::VertexStepMode::Vertex;
    }
    {
        wgpu::VertexBufferLayout& vertexBufferLayout = vertexBufferLayouts[1];
        vertexBufferLayout.attributeCount = 1;
        vertexBufferLayout.attributes = &vertexAttributes[1];
        vertexBufferLayout.arrayStride = sizeof(Vec2);
        vertexBufferLayout.stepMode = wgpu::VertexStepMode::Vertex;
    }

    Vector<wgpu::BindGroupLayoutEntry> bindGroupLayoutEntries(3, wgpu::Default);
    {
        wgpu::BindGroupLayoutEntry& bindGroupLayoutEntry = bindGroupLayoutEntries[0];
        bindGroupLayoutEntry.binding = 0;
        bindGroupLayoutEntry.visibility = wgpu::ShaderStage::Fragment;
        bindGroupLayoutEntry.sampler.type = wgpu::SamplerBindingType::Filtering;
    }
    {
        wgpu::BindGroupLayoutEntry& bindGroupLayoutEntry = bindGroupLayoutEntries[1];
        bindGroupLayoutEntry.binding = 1;
        bindGroupLayoutEntry.visibility = wgpu::ShaderStage::Fragment;
        bindGroupLayoutEntry.texture.sampleType = wgpu::TextureSampleType::Float;
        bindGroupLayoutEntry.texture.viewDimension = wgpu::TextureViewDimension::_2D;
    }
    {
        wgpu::BindGroupLayoutEntry& bindGroupLayoutEntry = bindGroupLayoutEntries[2];
        bindGroupLayoutEntry.binding = 2;
        bindGroupLayoutEntry.visibility = wgpu::ShaderStage::Vertex | wgpu::ShaderStage::Fragment;

        wgpu::BufferBindingLayout bufferBindingLayout = wgpu::Default;
        bufferBindingLayout.type = wgpu::BufferBindingType::Uniform;
        bufferBindingLayout.minBindingSize = sizeof(UniformData);
        bindGroupLayoutEntry.buffer = bufferBindingLayout;
    }

    std::string shaderSource = _DefaultVertexSource + _DefaultFragmentSource;

    _DefaultRenderPipeline = MakeRef<RenderPipeline>(shaderSource, vertexBufferLayouts, bindGroupLayoutEntries);

    DrawGroup drawGroup = {};
    drawGroup.pipeline = _DefaultRenderPipeline;
    _DrawGroups.emplace_back(std::move(drawGroup));
}

void Renderer::Shutdown()
{
    _DrawGroups.clear();
    _DefaultRenderPipeline.reset();
}

void Renderer::AddSprite(Sprite* sprite)
{
    for (auto& drawGroup : _DrawGroups)
    {
        if (drawGroup.pipeline == sprite->renderPipeline)
        {
            drawGroup.sprites.emplace_back(sprite);
            return;
        }
    }

    DrawGroup drawGroup = {};
    drawGroup.pipeline = sprite->renderPipeline;
    drawGroup.sprites = { sprite };
    _DrawGroups.emplace_back(std::move(drawGroup));
}

void Renderer::RemoveSprite(Sprite* sprite)
{
    for (auto& drawGroup : _DrawGroups)
    {
        if (drawGroup.pipeline != sprite->renderPipeline)
        {
            continue;
        }

        drawGroup.sprites.erase(std::remove(drawGroup.sprites.begin(), drawGroup.sprites.end(), sprite), drawGroup.sprites.end());
    }
}

void Renderer::Draw(wgpu::RenderPassEncoder renderPass)
{
    for (auto& drawGroup : _DrawGroups)
    {
        renderPass.setPipeline(*drawGroup.pipeline);
        // Instanced Draw Call
    }
}

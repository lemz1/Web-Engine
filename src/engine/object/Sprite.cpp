#include "Sprite.h"

#include "engine/render/Renderer.h"
#include "engine/util/AssetManager.h"
#include "engine/core/Application.h"
#include "engine/debug/Instrumentor.h"

Sprite::Sprite(
    Color color,
    Ref<RenderPipeline> renderPipeline
)
{
    Construct(MakeRef<Image>(&color, 1, 1, wgpu::TextureFormat::RGBA8Unorm), renderPipeline);
}

Sprite::Sprite(
    Ref<Image> image,
    Ref<RenderPipeline> renderPipeline
)
{
    Construct(image, renderPipeline);
}

Sprite::~Sprite()
{
    _bindGroup.release();
}

void Sprite::Draw(wgpu::RenderPassEncoder renderPass)
{
    if (!camera)
    {
        return;
    }
    
    UpdateModel();
    UniformData uniformData = {};
    uniformData.modelViewProjection = camera->GetProjection() * camera->GetInverseView() * _model;
    uniformData.tint = Color::Normalize(tint);
    _uniformBuffer->Write(&uniformData, sizeof(UniformData));

    renderPass.setPipeline(*renderPipeline);
    renderPass.setBindGroup(0, *_bindGroup, 0, nullptr);
    renderPass.setVertexBuffer(0, *_vertexBuffer, 0, _vertexBuffer->GetSize());
    renderPass.setVertexBuffer(1, *_texCoordBuffer, 0, _texCoordBuffer->GetSize());
    renderPass.draw(4, 1, 0, 0);
}

void Sprite::Construct(
    Ref<Image> image,
    Ref<RenderPipeline> renderPipeline
)
{
    this->image = image;

    if (renderPipeline)
    {
        this->renderPipeline = renderPipeline;
    }
    else
    {
        this->renderPipeline = Renderer::GetDefaultRenderPipeline();
    }

    Vector<Vec2> quad =
    {
        Vec2( 0.5f, -0.5f),
        Vec2(-0.5f, -0.5f),
        Vec2( 0.5f,  0.5f),
        Vec2(-0.5f,  0.5f),
    };
    _vertexBuffer = MakeScoped<Buffer>(wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst, quad.size() * sizeof(Vec2));
    _vertexBuffer->Write(quad.data(), _vertexBuffer->GetSize());

    Vector<Vec2> texCoords =
    {
        Vec2(1.0f, 1.0f),
        Vec2(0.0f, 1.0f),
        Vec2(1.0f, 0.0f),
        Vec2(0.0f, 0.0f),
    };
    _texCoordBuffer = MakeScoped<Buffer>(wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst, texCoords.size() * sizeof(Vec2));
    _texCoordBuffer->Write(texCoords.data(), _texCoordBuffer->GetSize());

    _uniformBuffer = MakeScoped<Buffer>(wgpu::BufferUsage::Uniform | wgpu::BufferUsage::CopyDst, sizeof(UniformData));

    _sampler = MakeScoped<Sampler>();

    Vector<wgpu::BindGroupEntry> bindGroupEntries(3, wgpu::Default);
    {
        wgpu::BindGroupEntry& bindGroupEntry = bindGroupEntries[0];
        bindGroupEntry.binding = 0;
        bindGroupEntry.offset = 0;
        bindGroupEntry.sampler = *_sampler;
    }
    {
        wgpu::BindGroupEntry& bindGroupEntry = bindGroupEntries[1];
        bindGroupEntry.binding = 1;
        bindGroupEntry.offset = 0;
        bindGroupEntry.textureView = *image;
    }
    {
        wgpu::BindGroupEntry& bindGroupEntry = bindGroupEntries[2];
        bindGroupEntry.binding = 2;
        bindGroupEntry.offset = 0;
        bindGroupEntry.buffer = *_uniformBuffer;
        bindGroupEntry.size = _uniformBuffer->GetSize();
    }

    _bindGroup = MakeScoped<BindGroup>(bindGroupEntries, this->renderPipeline->GetBindGroupLayout());
}

void Sprite::UpdateModel()
{
    _model  = glm::translate(Mat4Identity, transform.position);
    _model *= glm::mat4_cast(transform.rotation);
    float aspect = (float)image->GetWidth() / (float)image->GetHeight();
    _model *= glm::scale(Mat4Identity, Vec3(transform.scale.x * (0.5f * aspect), transform.scale.y, transform.scale.z));
}

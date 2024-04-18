#pragma once

#include "engine/wgpu/Image.h"
#include "engine/wgpu/Buffer.h"
#include "engine/wgpu/Sampler.h"
#include "engine/wgpu/BindGroup.h"
#include "engine/wgpu/RenderPipeline.h"
#include "engine/util/Types.h"
#include "engine/util/Color.h"
#include "engine/util/Transform.h"
#include "engine/render/Camera.h"

class Sprite 
{
public:
    Sprite(
        Color color,
        Ref<RenderPipeline> renderPipeline = nullptr
    );
    Sprite(
        Ref<Image> image,
        Ref<RenderPipeline> renderPipeline = nullptr
    );
    ~Sprite();

    void Draw(wgpu::RenderPassEncoder renderPass);

    void SetFilterMode(wgpu::FilterMode filterMode);
    wgpu::FilterMode GetFilterMode() const { return _filterMode; }
public:
    Ref<Image> image = nullptr;
    Ref<RenderPipeline> renderPipeline = nullptr;
    Ref<Camera> camera = nullptr;

    Transform transform{};
    Color tint{};
private:
    void Construct(
        Ref<Image> image,
        Ref<RenderPipeline> renderPipeline
    );

    void CreateBindGroup();

    void UpdateModel();
private:
    Scoped<Buffer> _vertexBuffer = nullptr;
    Scoped<Buffer> _texCoordBuffer = nullptr;
    Scoped<Buffer> _uniformBuffer = nullptr;
    Scoped<BindGroup> _bindGroup = nullptr;
    Scoped<Sampler> _sampler = nullptr;

    wgpu::FilterMode _filterMode = wgpu::FilterMode::Linear;

    Mat4 _model = Mat4Identity;
};

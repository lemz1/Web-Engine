#pragma once

#include "engine/wgpu/Buffer.h"
#include "engine/util/Types.h"
#include "engine/util/Image.h"
#include "engine/wgpu/RenderPipeline.h"

class Sprite 
{
public:
    Sprite();
    ~Sprite();

    void Draw(wgpu::RenderPassEncoder renderPass);

    static std::string_view GetDefaultVertexSource() { return Sprite::_VertexSource; }
    static std::string_view GetDefaultFragmentSource() { return Sprite::_FragmentSource; }
public:
    Ref<Image> image = nullptr;
    Ref<RenderPipeline> renderPipeline = nullptr;
private:
    static const char* _VertexSource;
    static const char* _FragmentSource;

    Scoped<Buffer> _vertexBuffer = nullptr;
    Scoped<Buffer> _texCoordBuffer = nullptr;
};

#include "Sprite.h"

#include "engine/util/AssetManager.h"

static Ref<RenderPipeline> SpriteRenderPipeline = nullptr;
static void CreateDefaultSpriteRenderPipeline();

Sprite::Sprite()
{
    if (!SpriteRenderPipeline) 
    {
        CreateDefaultSpriteRenderPipeline();
    }

    renderPipeline = SpriteRenderPipeline;

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
        Vec2(1.0f, 0.0f),
        Vec2(0.0f, 0.0f),
        Vec2(1.0f, 1.0f),
        Vec2(0.0f, 1.0f),
    };
    _texCoordBuffer = MakeScoped<Buffer>(wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst, texCoords.size() * sizeof(Vec2));
    _texCoordBuffer->Write(texCoords.data(), _texCoordBuffer->GetSize());
}

Sprite::~Sprite()
{}

void Sprite::Draw(wgpu::RenderPassEncoder renderPass)
{
    renderPass.setPipeline(*renderPipeline);
    renderPass.setVertexBuffer(0, *_vertexBuffer, 0, _vertexBuffer->GetSize());
    renderPass.setVertexBuffer(1, *_texCoordBuffer, 0, _texCoordBuffer->GetSize());
    renderPass.draw(4, 1, 0, 0);
}

const char* Sprite::_VertexSource = R"(
struct VertexInput {
    @location(0) position: vec2<f32>,
    @location(1) texCoord: vec2<f32>,
};

struct VertexOutput {
    @builtin(position) clipPosition: vec4<f32>,
    @location(0) texCoord: vec2<f32>,
};

@vertex
fn vsMain(in: VertexInput) -> VertexOutput {
    var out: VertexOutput;

    out.clipPosition = vec4<f32>(in.position, 0.0, 1.0);
    out.texCoord = in.texCoord;
    return out;
}
)";

const char* Sprite::_FragmentSource = R"(
struct VertexOutput {
    @builtin(position) clipPosition: vec4<f32>,
    @location(0) texCoord: vec2<f32>,
};

@fragment
fn fsMain(in: VertexOutput) -> @location(0) vec4<f32> {
	let color: vec3<f32> = vec3<f32>(in.texCoord, 0.0);
	let gammaCorrectedColor: vec3<f32> = pow(color, vec3<f32>(2.2));
	return vec4<f32>(gammaCorrectedColor, 1.0);
}
)";

void CreateDefaultSpriteRenderPipeline()
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

    SpriteRenderPipeline = MakeRef<RenderPipeline>(
        Sprite::GetDefaultVertexSource(), 
        Sprite::GetDefaultFragmentSource(), 
        vertexBufferLayouts
    );
}

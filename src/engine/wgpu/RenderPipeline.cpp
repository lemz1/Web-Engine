#include "RenderPipeline.h"

#include "engine/core/Application.h"

RenderPipeline::RenderPipeline(
	std::string_view vertexSource,
	std::string_view fragmentSource,
	const Vector<wgpu::VertexBufferLayout>& vertexBufferLayouts
)
{
    wgpu::Device device = Application::GetWGPUContext()->device;
    wgpu::Queue queue = Application::GetWGPUContext()->queue;
	wgpu::TextureFormat swapChainFormat = Application::GetWGPUContext()->swapChainFormat;
    
	_vertexModule = MakeScoped<ShaderModule>(vertexSource);
	_fragmentModule = MakeScoped<ShaderModule>(fragmentSource);

    wgpu::RenderPipelineDescriptor pipelineDesc = wgpu::Default;
    pipelineDesc.label = "Render Pipeline";

    pipelineDesc.vertex.bufferCount = (uint32_t)vertexBufferLayouts.size();
    pipelineDesc.vertex.buffers = vertexBufferLayouts.data();
    pipelineDesc.vertex.module = _vertexModule->GetShaderModule();
	pipelineDesc.vertex.entryPoint = "vsMain";
	pipelineDesc.vertex.constantCount = 0;
	pipelineDesc.vertex.constants = nullptr;

    pipelineDesc.primitive.topology = wgpu::PrimitiveTopology::TriangleStrip;
	pipelineDesc.primitive.stripIndexFormat = wgpu::IndexFormat::Undefined;
	pipelineDesc.primitive.frontFace = wgpu::FrontFace::CCW;
	pipelineDesc.primitive.cullMode = wgpu::CullMode::None;

    // Fragment State
    wgpu::FragmentState fragmentState;
	fragmentState.module = _fragmentModule->GetShaderModule();
	fragmentState.entryPoint = "fsMain";
	fragmentState.constantCount = 0;
	fragmentState.constants = nullptr;

	wgpu::BlendState blendState;
	blendState.color.srcFactor = wgpu::BlendFactor::SrcAlpha;
	blendState.color.dstFactor = wgpu::BlendFactor::OneMinusSrcAlpha;
	blendState.color.operation = wgpu::BlendOperation::Add;
	blendState.alpha.srcFactor = wgpu::BlendFactor::Zero;
	blendState.alpha.dstFactor = wgpu::BlendFactor::One;
	blendState.alpha.operation = wgpu::BlendOperation::Add;

	wgpu::ColorTargetState colorTarget;
	colorTarget.format = swapChainFormat;
	colorTarget.blend = &blendState;
	colorTarget.writeMask = wgpu::ColorWriteMask::All;

	fragmentState.targetCount = 1;
	fragmentState.targets = &colorTarget;

	pipelineDesc.fragment = &fragmentState;

	wgpu::DepthStencilState depthStencilState = wgpu::Default;
	depthStencilState.depthCompare = wgpu::CompareFunction::Less;
	depthStencilState.depthWriteEnabled = true;
	depthStencilState.format = DepthTexture::GetTextureFormat();
	depthStencilState.stencilReadMask = 0;
	depthStencilState.stencilWriteMask = 0;

	pipelineDesc.depthStencil = &depthStencilState;

	pipelineDesc.multisample.count = 1;
	pipelineDesc.multisample.mask = ~0u;
	pipelineDesc.multisample.alphaToCoverageEnabled = false;

    wgpu::PipelineLayoutDescriptor pipelineLayoutDesc = wgpu::Default;
    pipelineLayoutDesc.bindGroupLayoutCount = 0;
    _pipelineLayout = device.createPipelineLayout(pipelineLayoutDesc);
    pipelineDesc.layout = _pipelineLayout;

    _pipeline = device.createRenderPipeline(pipelineDesc);
}

RenderPipeline::~RenderPipeline()
{
    _pipeline.release();
    _pipelineLayout.release();
}

#pragma once

#include <string>
#include "engine/wgpu/Texture2D.h"
#include "engine/wgpu/RenderPipeline.h"

class AssetManager
{
public:
	static std::string GetFileContent(std::string_view filePath);
	static wgpu::ShaderModule LoadShaderModule(std::string_view filePath);
	static Ref<Texture2D> LoadTexture2D(
		std::string_view filePath,
		wgpu::TextureFormat textureFormat
	);
};

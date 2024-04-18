#pragma once

#include <string>
#include "engine/wgpu/Image.h"
#include "engine/wgpu/RenderPipeline.h"

class AssetManager
{
public:
	static std::string GetFileContent(std::string_view filePath);
	static wgpu::ShaderModule LoadShaderModule(std::string_view filePath);
	static Ref<Image> LoadImage(std::string_view filePath);
};

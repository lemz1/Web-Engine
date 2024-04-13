#include "AssetManager.h"

#include "engine/core/Application.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <stb_image/stb_image.h>

std::string AssetManager::GetFileContent(std::string_view filePath)
{
    std::ifstream file(filePath.data(), std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Couldn't find file: " << filePath << std::endl;
        #ifdef WE_DEBUG
        assert(false);
        #endif
        return "";
    }

    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    file.close();

    return content;
}

wgpu::ShaderModule AssetManager::LoadShaderModule(std::string_view filePath)
{
    wgpu::Device device = Application::GetWGPUContext()->device;
    std::string shaderSource = AssetManager::GetFileContent(filePath);

    wgpu::ShaderModuleWGSLDescriptor shaderCodeDesc;
    shaderCodeDesc.chain.next = nullptr;
    shaderCodeDesc.chain.sType = wgpu::SType::ShaderModuleWGSLDescriptor;
    shaderCodeDesc.code = shaderSource.c_str();

    wgpu::ShaderModuleDescriptor shaderDesc;
    shaderDesc.nextInChain = &shaderCodeDesc.chain;
    shaderDesc.hintCount = 0;
    shaderDesc.hints = nullptr;
    
    return device.createShaderModule(shaderDesc);
}

Ref<Texture2D> AssetManager::LoadTexture2D(
    std::string_view filePath,
    wgpu::TextureFormat textureFormat
)
{
    void* pixels;
    int width;
    int height;
    int numComponents;
    switch (textureFormat)
    {
        case wgpu::TextureFormat::RGBA8Unorm:
            pixels = stbi_load(filePath.data(), &width, &height, &numComponents, 4);
            break;
        case wgpu::TextureFormat::RGBA32Float:
            pixels = stbi_loadf(filePath.data(), &width, &height, &numComponents, 4);
            break;
        default:
            std::cerr << "texture format not supported: " << textureFormat << std::endl;
            return nullptr;
    }

    return MakeRef<Texture2D>(pixels, width, height, textureFormat);
}

#pragma once

#include "engine/object/Sprite.h"
#include "engine/util/Types.h"

struct UniformData
{
	Mat4 modelViewProjection;
	Vec4 tint;
};

struct DrawGroup
{
	Ref<RenderPipeline> pipeline = nullptr;
	Scoped<Buffer> uniformBuffer = nullptr;
	Vector<Sprite*> sprites = {};
};

class Renderer
{
public:
	static void Init();
	static void Shutdown();

	static void AddSprite(Sprite* sprite);
	static void RemoveSprite(Sprite* sprite);
	static void Draw(wgpu::RenderPassEncoder renderPass);

	static const Vector<DrawGroup>& GetDrawGroups() { return _DrawGroups; }
	static std::string_view GetDefaultVertexSource() { return _DefaultVertexSource; }
	static std::string_view GetDefaultFragmentSource() { return _DefaultFragmentSource; }
	static const Ref<RenderPipeline>& GetDefaultRenderPipeline() { return _DefaultRenderPipeline; }
private:
	static Vector<DrawGroup> _DrawGroups;

	static std::string _DefaultVertexSource;
	static std::string _DefaultFragmentSource;
	static Ref<RenderPipeline> _DefaultRenderPipeline;
};

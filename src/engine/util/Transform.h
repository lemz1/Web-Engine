#pragma once

#include "engine/util/Types.h"

struct Transform
{
	Transform() = default;
	Transform(const Vec3& position)
	:	position(position)
	{}

	Vec3 position = Vec3(0.0f);
	Quat rotation = QuatIdentity;
	Vec3 scale = Vec3(1.0f);
};

#pragma once

#include "engine/util/Types.h"

struct Transform
{
	Vec3 position = Vec3(0.0f);
	Quat rotation = QuatIdentity;
	Vec3 scale = Vec3(1.0f);
};

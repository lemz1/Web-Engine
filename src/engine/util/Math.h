#pragma once

#include "engine/util/Types.h"
#include <cmath>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Math
{
public:
	static float Sign(float value);
	static float Lerp(
		float a,
		float b,
		float t
	);
	static float Clamp(
		float value,
		float min,
		float max
	);
	static float RemapToRange(
		float value,
		float oldMin,
		float oldMax,
		float newMin,
		float newMax
	);
};

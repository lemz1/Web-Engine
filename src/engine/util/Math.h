#pragma once

#include "engine/util/Types.h"

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
	static float Max(
		float a,
		float b
	);
	static float Min(
		float a,
		float b
	);
};

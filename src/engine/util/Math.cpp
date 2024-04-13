#include "Math.h"

float Math::Sign(float value)
{
	return (value > 0) ? +1.0f
		:  (value < 0) ? -1.0f
		:				  0.0f;
}

float Math::Lerp(
	float a, 
	float b, 
	float t
)
{
    return a + t * (b - a);
}

float Math::Clamp(
	float value, 
	float min, 
	float max
)
{
    return (value < min) ? min
		:  (value > max) ? max
		:				 value;
}

float Math::RemapToRange(
	float value, 
	float oldMin, 
	float oldMax, 
	float newMin, 
	float newMax
)
{
    return (value - oldMax) / (oldMax - oldMin) * (newMax - newMin) + newMin;
}

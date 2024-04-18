#pragma once

#include "engine/util/Math.h"

union ColorData
{
	uint32_t hex;
	struct
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
};

class Color
{
public:
	Color()
	{
		this->color = { 0xFFFFFFFF };
	}

	Color(ColorData color) 
	{
		this->color = color;
	}

	// hex as RGBA meaing 0xALPHA_BLUE_GREEN_RED
	Color(uint32_t hex)
	{
		this->color.hex = hex;
	}

	Color(
		uint8_t r,
		uint8_t g,
		uint8_t b,
		uint8_t a = 255
	)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	Color(const Vec3& rgb) 
	{
		color.r = rgb.r;
		color.g = rgb.g;
		color.b = rgb.b;
		color.a = 255;
	}
	
	Color(const Vec4& rgba)
	{
		color.r = rgba.r;
		color.g = rgba.g;
		color.b = rgba.b;
		color.a = rgba.a;
	}

	operator uint32_t() { return color.hex; }
	operator Vec3() { return Vec3(color.r, color.g, color.b); }
	operator Vec4() { return Vec4(color.r, color.g, color.b, color.a); }

	static Vec4 Normalize(Color color)
	{
		Vec4 normalizedColor = Vec4(0.0f);
		normalizedColor.r = color.color.r / 255.0f;
		normalizedColor.g = color.color.g / 255.0f;
		normalizedColor.b = color.color.b / 255.0f;
		normalizedColor.a = color.color.a / 255.0f;

		return normalizedColor;
	}
public:
	ColorData color;
};

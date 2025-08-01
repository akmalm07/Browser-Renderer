#pragma once

#include "config.h"

struct ImVec3
{
	float x, y, z;
	constexpr ImVec3() : x(0), y(0), z(0) {}
	constexpr ImVec3(float x, float y, float z) : x(x), y(y), z(z) {}


	ImVec3(const ImVec2& vec2, float z = 0.0f) : x(vec2.x), y(vec2.y), z(z) {}
	ImVec3(const ImVec4& vec4) : x(vec4.x), y(vec4.y), z(vec4.z) {}
	ImVec3(const ImVec3& other) : x(other.x), y(other.y), z(other.z) {}

	ImVec3& operator=(const ImVec3& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}
	ImVec3 operator+(const ImVec3& other) const
	{
		return ImVec3(x + other.x, y + other.y, z + other.z);
	}
	ImVec3 operator-(const ImVec3& other) const
	{
		return ImVec3(x - other.x, y - other.y, z - other.z);
	}
};


inline float clamp(float value, float min, float max)
{
	return (value < min) ? min : (value > max) ? max : value;
}


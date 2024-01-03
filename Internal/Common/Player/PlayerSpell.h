#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>

#include "../../Library/vector/Vector3.h"

class PlayerSpell {
public:
	PlayerSpell(float cast_range, float missile_speed, float missile_width, std::string type, std::string name)
	{
		this->cast_range = cast_range;
		this->missile_speed = missile_speed;
		this->missile_width = missile_width;
		this->type = type;
		this->name = name;
	}

	float cast_range;
	float cast_radius;
	float missile_speed;
	float missile_width;

	std::string type;
	std::string name;
};
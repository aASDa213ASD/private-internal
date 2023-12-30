#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>

#include "../../Library/vector/Vector3.h"

class Spell {
public:
	uint64_t ptr;

	//bool OnEvade = false;
	//bool Missile = false;

	int lvl;
	int charges;
	int slot;

	float ready_at;
	float cooldown;
	float speed;
	float cast_time;
	float cast_start;
	float cast_end;

	Vector3 position;
	Vector3 start_pos;
	Vector3 end_pos;

	std::string name;
};
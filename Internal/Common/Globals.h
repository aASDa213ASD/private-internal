#pragma once

#include <cstdint>
#include <vector>

#include "../Common/Player.h"

namespace globals {
	extern uintptr_t base;
	extern uintptr_t gadget;
	extern uint64_t vmt_ops;

	extern float multipliedMatrix[16];
	extern float viewMatrix[16];
	extern float projMatrix[16];
	extern float viewProjMatrix[16];

	extern std::vector<Player> enemies;
	extern Player local;
}
#include "Globals.h"

namespace globals {
	uintptr_t base = NULL;
	uintptr_t gadget = NULL;
	uint64_t vmt_ops = NULL;

	float multipliedMatrix[16] = {};
	float viewMatrix[16] = {};
	float projMatrix[16] = {};
	float viewProjMatrix[16] = {};

	std::vector<Player> enemies = {};
	Player Local = NULL;
}

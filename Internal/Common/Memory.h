#pragma once

#include <cstdint>
#include <vector>

#include "Player.h"

class Memory {
public:
	uintptr_t base;
	uintptr_t gadget;

	uint64_t vmt_on_process_spell;

	//float multipliedMatrix[16];
	//float viewMatrix[16];
	//float projMatrix[16];
	//float viewProjMatrix[16];

	std::vector<Player> enemies;
	std::vector<Player> allies;
	Player local = Player(NULL);

	void initialize(bool with_players = true);
};

inline Memory memory;
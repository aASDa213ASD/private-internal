#pragma once

#include <cstdint>
#include <vector>

#include "Player/Player.h"
#include "../../Features/Evade/Spell/Spell.h"

class Memory {
public:
	uintptr_t base;
	uintptr_t gadget;

	uint32_t viewport_height;
	uint32_t viewport_width;

	uint64_t vmt_on_process_spell;

	//float multipliedMatrix[16];
	//float viewMatrix[16];
	//float projMatrix[16];
	//float viewProjMatrix[16];

	std::vector<Player> enemies;
	std::vector<Player> allies;
	std::vector<Spell> active_missiles;
	Player local = Player(NULL);

	void initialize(bool with_players = true);
	void get_viewport_resolution();
};

inline Memory memory;
#pragma once

#include <string>

#include "../../Library/vector/Vector.h"
#include "../../Offsets/Functions.h"
#include "PlayerSpell.h"

class Player {
private:
	uintptr_t   _pointer;
	int			_team;
	std::string _hero_name;

public:
	Player(uintptr_t pointer);

	std::string _name;

	uintptr_t	address();
	std::string name();
	std::string hero_name();
	float		health();
	float		attack_range();
	int			team();
	bool		is_enemy_to(Player player);
	bool		is_ally_to(Player player);
	Vector3		position();

	std::vector<PlayerSpell> spells;
	void load_spelldb();
};
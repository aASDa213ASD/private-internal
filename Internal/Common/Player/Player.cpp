#include "Player.h"

#include <format>
#include <fstream>

#include "../../Offsets/Player.h"
#include "../../Library/JSON.h"
#include "../Memory.h"

using namespace nlohmann;

typedef float(__fastcall* FnGetBoundingRadius)(uint64_t* entity);
typedef bool(__fastcall* FnIsAlive)(uint64_t* entity);

Player::Player(uintptr_t pointer = NULL)
{
	if (pointer)
	{
		_pointer   = pointer;
		_name      = *reinterpret_cast<std::string*>(pointer + Name);
		_hero_name = *reinterpret_cast<std::string*>(pointer + HeroName);
		_team      = *reinterpret_cast<int*>(pointer + Team);
	}
	else
	{
		_pointer   = pointer;
		_name      = "Unnamed";
		_hero_name = "Unknown";
		_team	   = -1;
	}
}

void Player::load_spelldb()
{
	json j;
	std::ifstream i(std::format("C:/Users/aasda/source/repos/Internal/Build/SpellDB/{}.json", this->_hero_name));
	i >> j;

	if (j[this->_hero_name].contains("Spells"))
	{
		for (const auto& [spell_name, spell_data] : j[this->_hero_name]["Spells"].items())
		{
			float cast_range = spell_data.value("castRange", 0);
			float missile_speed = spell_data.value("missileSpeed", 0);
			float missile_width = spell_data.value("mLineWidth", 0);
			std::string type = spell_data.value("mTargetingTypeData", "None");
			spells.emplace_back(PlayerSpell(cast_range, missile_speed, missile_width, type, spell_name));
		}
	}
}

uintptr_t Player::address()
{
	return this->_pointer;
}

std::string Player::name()
{
	return this->_name;
}

std::string Player::hero_name()
{
	return this->_hero_name;
}

float Player::health()
{
	return *reinterpret_cast<float*>(_pointer + Health);
}

float Player::attack_range()
{
	return *reinterpret_cast<float*>(_pointer + AttackRange);
}

float Player::bounding_radius()
{
	FnGetBoundingRadius get_bounding_radius = reinterpret_cast<FnGetBoundingRadius>(memory.base + fGetBoundingRadius);
	return get_bounding_radius((uint64_t*)_pointer);
}

int Player::team()
{
	return this->_team;
}

bool Player::is_enemy_to(Player player)
{
	return (_team != player.team());
}

bool Player::is_ally_to(Player player)
{
	return (_team == player.team());
}

bool Player::is_alive()
{
	FnIsAlive is_alive = reinterpret_cast<FnIsAlive>(memory.base + fIsAlive);
	return is_alive((uint64_t*)_pointer);
}

bool Player::is_visible()
{
	return *(bool*)(_pointer + IsVisible);
}

Vector3 Player::position()
{
	return *reinterpret_cast<Vector3*>(_pointer + Position);
}
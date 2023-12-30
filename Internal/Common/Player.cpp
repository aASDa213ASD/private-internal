#include "Player.h"

#include "../Offsets/Player.h"

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
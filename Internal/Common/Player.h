#pragma once

#include <string>

#include "../Library/vector/Vector.h"

/*
class Player {
public:
	//int target_priority;

	Player(uintptr_t pointer);
	void initialize();

	void getName();
	void getChampionName();
	//void getPointer();
	float getHealth();
	float getMana();
	Vector3 getPosition();
	Vector2 getDirection(); // Position.x + (Velocity * direction.x * time)

	uintptr_t ptr;
	bool alive;
	bool visible;
	float last_visible_time;
	float last_invisible_time;
	char name[15];
	char champion_name[35];

	int combat_type;
	int team;
	float health;
	float mana;
	Vector3 position;
	Vector2 on_screen;
	float attack_range;
	float attack_delay;
	float attack_cast_delay;
	float ad_base;
	float ad_bonus;
	float ap;
	Vector2 direction;
	//buffmanager* _buffmanager = new buffmanager();
	//std::vector<buff> active_buffs = {};
	//spellbook spellbook;
	//spell spells[6];
	bool is_cced();
	bool HasBuff(int type);
	//bool HasBuffName(string name);
	//AiManager pAiManager;
	//std::vector<Vector3>
	//std::vector<PlayerSpell> Abilities = {};


	//void Update(); ёзлесс?
	std::vector<Vector3> currentNode(std::vector<Vector3> points);
	std::vector<Vector3> NextNode(std::vector<Vector3> points);
	//vector<buff> buffs = {};

};
*/

class Player {
private:
	uintptr_t   _pointer;
	std::string _name;
	std::string _hero_name;
	int			_team;

public:
	Player(uintptr_t pointer);

	uintptr_t	address();
	std::string name();
	std::string hero_name();
	float		health();
	int			team();
	bool		is_enemy_to(Player player);
	bool		is_ally_to(Player player);
};
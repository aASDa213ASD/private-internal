#include "SkinChanger.h"

#include <ranges>

#include "Riot/GameClasses.h"
#include "../../Common/Memory.h"
#include "../../Library/FNVHash.h"

void SkinChanger::load()
{
	skin_database.parse();
}

void SkinChanger::update() {}

void SkinChanger::unload() {}

std::vector<SkinDatabase::skin_info>& SkinChanger::get_skins(uintptr_t player_address)
{
	const auto player = *reinterpret_cast<AIBaseCommon**>(memory.base + player_address);

	if (player)
		return skin_database.champions_skins[
			fnv::hash_runtime(player->get_character_data_stack()->base_skin.model.str)
		];

	std::vector<SkinDatabase::skin_info> vector;
	return vector;
}

void SkinChanger::change_skin(const char* model_name, int skin_id, uintptr_t player_address)
{
	const auto player = *reinterpret_cast<AIBaseCommon**>(memory.base + player_address);

	if (player)
		player->change_skin(model_name, skin_id);
}

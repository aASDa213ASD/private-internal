#include "SkinDatabase.h"


#include <algorithm>
#include <cstdint>
#include <map>
#include <ranges>
#include <string>
#include <utility>

#include "../../Library/FNVHash.h"
#include "../../Common/Memory.h"
#include "../../Offsets/Objects.h"
#include "../../Offsets/Skins.h"
#include "../Riot/GameClasses.h"

void SkinDatabase::parse()
{
	auto championg_manager = *reinterpret_cast<ChampionManager**>(memory.base + oChampionManager);

	for (const auto& champion : championg_manager->champions) {
		std::vector<std::int32_t> skins_ids;
		std::string skin_name;

		for (auto i{ 0u }; i < champion->skins.size; ++i)
			skins_ids.push_back(champion->skins.list[i].skin_id);

		std::ranges::sort(skins_ids);
		std::sort(skins_ids.begin(), skins_ids.end());

		for (const auto& i : skins_ids) {
			const auto skin_display_name{ std::string("game_character_skin_displayname_") + champion->champion_name.str + "_" + std::to_string(i) };
			skin_name = champion->champion_name.str + std::string(": ") + std::to_string(i);

			const auto champ_name{ fnv::hash_runtime(champion->champion_name.str) };
			this->champions_skins[champ_name].push_back({ champion->champion_name.str, skin_name, i });
		}
	}
}

#include "Memory.h"

#include "Spoof.h"
#include "../Offsets/Objects.h"
#include "../Offsets/Player.h"

void Memory::initialize(bool with_players)
{
	base   = reinterpret_cast<std::uintptr_t>(::GetModuleHandle(nullptr));
	gadget = GetAddressFromSignature({ 0xff, 0x23 }, base, 0xffffffffffff);

	if (with_players)
	{
		local = Player(*reinterpret_cast<uintptr_t*>(base + LocalPlayer));

		uintptr_t hero_list	   = *reinterpret_cast<uintptr_t*>(base + HeroList);
		uintptr_t local_player = *reinterpret_cast<uintptr_t*>(hero_list + 0x8);
		int hero_list_size	   = *reinterpret_cast<int*>(hero_list + 0x8 + 0x8);

		for (auto i = 0; i < hero_list_size; ++i) {
			uintptr_t player_address = *reinterpret_cast<uintptr_t*>(local_player + 0x8 * i);

			if (*reinterpret_cast<int*>(player_address + Team) != local.team())
				enemies.emplace_back(Player(player_address));
			else
				allies.emplace_back(Player(player_address));
		}
	}
}
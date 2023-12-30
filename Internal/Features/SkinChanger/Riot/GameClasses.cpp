#include "GameClasses.h"

#include "../../Offsets/Skins.h"
#include "../../Common/Memory.h"
#include "../../Library/Encryption.h"

/* If you wont encrypt skin id the game will reset your skin after death */
void AIBaseCommon::change_skin(const char* model, const std::int32_t skin) noexcept
{
	const auto stack{ this->get_character_data_stack() };
	reinterpret_cast<xor_value<std::int32_t>*>(std::uintptr_t(this) + oSkinID)->encrypt(skin);
	stack->base_skin.skin = skin;
	stack->update(true);
}

void CharacterDataStack::push(const char* model, const std::int32_t skin) const noexcept
{
	using push_t = __int64(__fastcall*)(std::uintptr_t, const char*, std::int32_t, std::int32_t, bool, bool, bool, bool, bool, bool, std::int8_t, const char*, std::int32_t, const char*, std::int32_t, bool, std::int32_t);
	static const auto _push{ reinterpret_cast<push_t>(memory.base + oCharacterDataStack_Push) };
	_push(std::uintptr_t(this), model, skin, 0, false, false, false, false, true, false, -1, "\x00", 0, "\x00", 0, false, 1);
}

void CharacterDataStack::update(const bool change) const noexcept
{
	static const auto _update{ reinterpret_cast<__int64(__fastcall*)(std::uintptr_t, bool)>(memory.base + oCharacterDataStack_Update) };
	_update(std::uintptr_t(this), change);
}

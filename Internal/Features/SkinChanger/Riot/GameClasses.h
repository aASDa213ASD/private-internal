#pragma once

#include <vector>
#include <cinttypes>
#include <string>
#include <memory>
#include <map>
#include <unordered_map>
#include <Windows.h>

#include "../../Offsets/Player.h"
#include "../../Offsets/Skins.h"

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PAD(SIZE) uint8_t MACRO_CONCAT(_pad, __COUNTER__)[SIZE];

class GameObject {
public:
	[[nodiscard]] inline std::string* get_name() const noexcept {
		return reinterpret_cast<std::string*>(std::uintptr_t(this) + Name);
	}

	[[nodiscard]] inline std::int32_t get_team() const noexcept {
		return *reinterpret_cast<std::int32_t*>(std::uintptr_t(this) + Team);
	}
};

class AString {
public:
	const char* str;
	std::int32_t length;
	std::int32_t capacity;
};

template <class T>
class RiotArray {
public:
	T* list;
	std::int32_t size;
	std::int32_t cap;
};

class Skin {
public:
	std::int32_t skin_id;
	std::int32_t unknown; // always 0x1f4
	AString skin_name;
};

class CharacterStackData {
public:
	AString model;
	PAD(0x10)
	std::int32_t skin;
	PAD(0x60)
	std::int8_t gear;
	PAD(0x7)
};

class CharacterDataStack {
public:
	std::vector<CharacterStackData> stack;
	CharacterStackData base_skin;

	void update(const bool change) const noexcept;
	void push(const char* model, const std::int32_t skin) const noexcept;
};

class AIBaseCommon : public GameObject {
public:
	CharacterDataStack* get_character_data_stack() const noexcept { return reinterpret_cast<CharacterDataStack*>(std::uintptr_t(this) + oCharacterDataStack); }
	void change_skin(const char* model, const std::int32_t skin) noexcept;
};

class Champion {
public:
	PAD(0x8)
	AString champion_name;
	PAD(0xD0)
	RiotArray<Skin> skins;
};

class ChampionManager {
public:
	PAD(0x18)
	std::vector<Champion*> champions;
};

#pragma once

#include <Windows.h>
#include <string>

#include "../Feature.h"
#include "Database/SkinDatabase.h"

class SkinChanger : public Feature {
private:
	std::string name = "Skins";
	SkinDatabase skin_database;

public:
	void load() override;
	void update() override;
	void unload() override;
	const std::string& get_name() const override { return name; };

	std::vector<SkinDatabase::skin_info>& get_skins(uintptr_t player_address);
	void change_skin(const char* model_name, int skin_id, uintptr_t player_address);
	std::string* change_name(uintptr_t player_address);
};
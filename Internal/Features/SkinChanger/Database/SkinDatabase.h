#pragma once

#include <string>
#include <vector>
#include <map>

class SkinDatabase {
public:
	class skin_info {
	public:
		const char* model_name;
		std::string  skin_name;
		std::int32_t skin_id;
	};

	std::map<uintptr_t, std::vector<skin_info>> champions_skins;
	void parse();
};

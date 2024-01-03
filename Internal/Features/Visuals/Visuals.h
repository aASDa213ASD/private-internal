#pragma once

#include <Windows.h>
#include <string>
#include <thread>

#include "../Feature.h"

class Visuals : public Feature {
private:
	std::string name = "Visuals";

public:
	void load() override;
	void update() override;
	void unload() override;
	const std::string& get_name() const override { return name; };

	bool draw_attack_range = true;
};
#pragma once

#include <Windows.h>
#include <string>

#include "../Feature.h"

class Evade : public Feature {
private:
	std::string name = "Evade";
	void thread_on_process_spell();

public:
	void load() override;
	void update() override;
	void unload() override;
	const std::string& get_name() const override { return name; };
};
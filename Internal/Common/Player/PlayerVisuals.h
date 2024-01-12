#pragma once

class PlayerVisuals {
public:
	bool attack_range = false;
	bool attack_range_rgb = false;
	float attack_range_color[4] = { 1.f, 1.f, 1.f, 1.f };

	bool hero_name = false;
	bool hero_name_rgb = false;
	float hero_name_color[4] = { 1.f, 1.f, 1.f, 1.f };
};
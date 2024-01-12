#include "Visuals.h"

#include "VisualsHelper.h"
#include "../../Common/Memory.h"
#include "../../Overlay/Render.h"
#include "../../Library/vector/Vector2.h"
#include "../../Library/imgui/imgui.h"

#include "../../Common/WorldToScreen.h"
#include "../../Common/WorldToMinimap.h"

void Visuals::load() {}

void Visuals::update()
{
	// TODO: Out of sight text
	// TODO: Minimap last_time_seen + position (WorldToMinimap.h)

    /* RGB Hue */
	ImVec4 gradient_color = ImColor::HSV(hue, 1.0f, 1.0f).Value;
    hue += 0.1f * ImGui::GetIO().DeltaTime;
    if (hue > 1.0f)
        hue -= 1.0f;

	for (auto& ally : memory.allies)
	{
		if (!ally.is_alive() || !ally.is_visible())
			continue;

		if (ally.visuals.attack_range)
		{
			if (ally.visuals.attack_range_rgb)
				render.circle_w2s(ally.position(), ImVec4(gradient_color.x, gradient_color.y, gradient_color.z, 1.f), (ally.attack_range() + ally.bounding_radius()), 180, 1.f, 15.f);
			else
				render.circle_w2s(ally.position(), *(ImColor*)ally.visuals.attack_range_color, (ally.attack_range() + ally.bounding_radius()), 180, 1.f, 15.f);
		}
		
		if (ally.visuals.hero_name)
		{
			if (ally.visuals.hero_name_rgb)
				render.text(world_to_screen(ally.position()), ally.hero_name(), ImVec4(gradient_color.x, gradient_color.y, gradient_color.z, 1.f), true, true);
			else
				render.text(world_to_screen(ally.position()), ally.hero_name(), *(ImColor*)ally.visuals.hero_name_color, true, true);
		}
	}

	for (auto& enemy : memory.enemies)
	{
		if (track_enemies)
		{
			float game_time = *reinterpret_cast<float*>(memory.base + GameTime);

			if (enemy.is_visible() || (enemy.last_seen_position.Distance(enemy.position()) > 1))
			{
				enemy.last_seen_time = game_time;
				enemy.last_seen_position = enemy.position();
			}
			else
			{
				Vector2 enemy_minimap_location = world_to_minimap(enemy.position());
				render.text(enemy_minimap_location, enemy.hero_name(), ImColor(1.f, 1.f, 1.f, 1.f), true, true);
				render.text(enemy_minimap_location - Vector2(0, 12), format_time(game_time - enemy.last_seen_time), ImColor(1.f, 1.f, 1.f, 1.f), true, true);
			}
		}

		if (!enemy.is_alive() || !enemy.is_visible())
			continue;

		if (enemy.visuals.attack_range)
		{
			if (enemy.visuals.attack_range_rgb)
				render.circle_w2s(enemy.position(), ImVec4(gradient_color.x, gradient_color.y, gradient_color.z, 0.7f), (enemy.attack_range() + enemy.bounding_radius()), 180, 1.0f, 15.f);
			else
				render.circle_w2s(enemy.position(), *(ImColor*)enemy.visuals.attack_range_color, (enemy.attack_range() + enemy.bounding_radius()), 180, 1.0f, 15.f);
		}

		if (enemy.visuals.hero_name)
		{
			if (enemy.visuals.hero_name_rgb)
				render.text(world_to_screen(enemy.position()), enemy.hero_name(), ImVec4(gradient_color.x, gradient_color.y, gradient_color.z, 1.f), true, true);
			else
				render.text(world_to_screen(enemy.position()), enemy.hero_name(), *(ImColor*)enemy.visuals.hero_name_color, true, true);
		}
	}
}

void Visuals::unload() {}
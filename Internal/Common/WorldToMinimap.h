#pragma once

#include "../Common/Memory.h"
#include "../Offsets/World.h"
#include "../Library/vector/Vector2.h"
#include "../Library/vector/Vector3.h"

static Vector2 world_to_minimap(const Vector3& world_position)
{
	float world_size = 14800.0f;

	uint64_t minimap_instance = *reinterpret_cast<uint64_t*>(memory.base + MinimapInstance);
	uint64_t minimap_hud	  = *reinterpret_cast<uint64_t*>(minimap_instance + MinimapHud);
	Vector2 minimap_position  = *reinterpret_cast<Vector2*>(minimap_hud + MinimapHudPosition);
	float minimap_size		  = *reinterpret_cast<float*>(minimap_hud + MinimapHudSize);

	float scale_factor = minimap_size / world_size;

	float minimap_x = (world_position.x * scale_factor) + minimap_position.x;
	float minimap_y = minimap_position.y + minimap_size - (world_position.z * scale_factor);

	return Vector2(minimap_x, minimap_y);
}
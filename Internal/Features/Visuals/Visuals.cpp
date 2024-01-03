#include "Visuals.h"

#include "../../Common/Memory.h"
#include "../../Common/WorldToScreen.h"
#include "../../Overlay/Render.h"
#include "../../Library/vector/Vector2.h"
#include "../../Library/imgui/imgui.h"

void Visuals::load() {}

void Visuals::update()
{
	if (draw_attack_range)
	{
		render.circle_w2s(memory.local.position(), ImColor(1.f, 0.f, 0.f, 1.f), memory.local.attack_range(), 80, 5.f);
		render.text(WorldToScreen(memory.local.position()), "Attack Range: ON", ImColor(1.f, 1.f, 1.f, 1.f), true, true);
	}
}

void Visuals::unload() {}
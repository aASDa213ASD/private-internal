#pragma once

#include "../Library/imgui/imgui_internal.h"

namespace ImGui
{
	static void Helpmark(const char* desc)
	{
		ImGui::SameLine();
		TextDisabled("(?)");
		if (IsItemHovered())
		{
			BeginTooltip();
			PushTextWrapPos(GetFontSize() * 35.0f);
			TextUnformatted(desc);
			PopTextWrapPos();
			EndTooltip();
		}
	}
}
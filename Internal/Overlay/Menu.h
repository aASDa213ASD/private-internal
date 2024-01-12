#pragma once

#include "../../Library/imgui/imgui.h"
#include "../Offsets/Objects.h"
#include "Common/Memory.h"

#include "../../Features/Featurectl.h"
#include "../../Features/SkinChanger/SkinChanger.h"
#include "../../Features/Visuals/Visuals.h"
#include "../Features/SkinChanger/Database/SkinDatabase.h"
#include "../../Common/Player/PlayerSpell.h"
#include "../Common/WorldToMinimap.h"

class Menu {
	ImGuiWindowFlags window_flags = 0;
	ImVec2 menu_size = ImVec2(150.0f, 140.0f);
	std::int32_t current_combo_skin_index{ 0 };

public:
	char spells[256] = "";
	bool is_opened = true;

	void aquire_styles()
	{
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(12.0f, 14.0f);
		style->WindowRounding = 0.0f;
		style->FramePadding = ImVec2(10.0f, 4.0f);
		style->FrameRounding = 0.0f;
		style->ItemSpacing = ImVec2(12.0f, 16.0f);
		style->ItemInnerSpacing = ImVec2(14.0f, 4.0f);
		style->IndentSpacing = 0.0f;
		style->ScrollbarSize = 12.0f;
		style->ScrollbarRounding = 2.0f;
		style->GrabMinSize = 4.0f;
		style->GrabRounding = 0.0f;
		style->WindowBorderSize = 0.0f;
		style->PopupBorderSize = 1.0f;
		style->GrabMinSize = 14.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.88f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.07f, 0.70f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.05f, 0.07f, 0.80f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.60f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.61f, 0.61f, 0.61f, 0.54f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.85f, 0.85f, 0.85f, 0.54f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 0.75f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.42f, 1.0f, 0.93f, 0.75f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.41f, 1.0f, 0.93f, 0.92f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		window_flags |= ImGuiWindowFlags_NoCollapse;

		ImGui::SetNextWindowSize(menu_size, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(960, 540));
		ImGui::SetColorEditOptions(ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoInputs);

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDrawCursor = false;
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	}

	void render()
	{	
		static const auto vector_getter_skin = [](void* vec, std::int32_t idx, const char** out_text) noexcept {
			const auto& vector{ *static_cast<std::vector<SkinDatabase::skin_info>*>(vec) };
			if (idx < 0 || idx > static_cast<std::int32_t>(vector.size())) return false;
			*out_text = idx == 0 ? "Default" : vector.at(idx - 1).skin_name.c_str();
			return true;
		};

		auto skin_changer = dynamic_cast<SkinChanger*>(featurectl.get_feature("Skins"));
		auto visuals = dynamic_cast<Visuals*>(featurectl.get_feature("Visuals"));

		if (ImGui::Begin("menu", nullptr, window_flags))
		{
			if (skin_changer)
				if (ImGui::BeginMenu("Skins"))
				{
					auto& values = skin_changer->get_skins(LocalPlayer);
					if (ImGui::Combo(
						"Skin", &current_combo_skin_index, vector_getter_skin,
						static_cast<void*>(&values), values.size() + 1)
						) {
						if (current_combo_skin_index > 0) {
							skin_changer->change_skin(
								values[current_combo_skin_index - 1].model_name,
								values[current_combo_skin_index - 1].skin_id,
								LocalPlayer
							);
						}
					}

					ImGui::EndMenu();
				}

			if (visuals)
				if (ImGui::BeginMenu("Visuals"))
				{
					if (ImGui::BeginMenu("Players"))
					{
						for (auto& ally : memory.allies)
						{
							if (ImGui::BeginMenu(ally.hero_name().c_str()))
							{
								ImGui::Checkbox("Attack range", &ally.visuals.attack_range);
								ImGui::SameLine();
								ImGui::ColorEdit4("###Attack range color", (float*)&ally.visuals.attack_range_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
								ImGui::Checkbox("Attack range RGB", &ally.visuals.attack_range_rgb);

								ImGui::Checkbox("Name", &ally.visuals.hero_name);
								ImGui::SameLine();
								ImGui::ColorEdit4("###Name color", (float*)&ally.visuals.hero_name_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
								ImGui::Checkbox("Name RGB", &ally.visuals.hero_name_rgb);
								ImGui::EndMenu();
							}
						}

						ImGui::Separator();

						for (auto& enemy : memory.enemies)
						{
							if (ImGui::BeginMenu(enemy.hero_name().c_str()))
							{
								ImGui::Checkbox("Attack range", &enemy.visuals.attack_range);
								ImGui::SameLine();
								ImGui::ColorEdit4("###Attack range color", (float*)&enemy.visuals.attack_range_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
								ImGui::Checkbox("Attack range RGB", &enemy.visuals.attack_range_rgb);

								ImGui::Checkbox("Name", &enemy.visuals.hero_name);
								ImGui::SameLine();
								ImGui::ColorEdit4("###Name color", (float*)&enemy.visuals.hero_name_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
								ImGui::Checkbox("Name RGB", &enemy.visuals.hero_name_rgb);
								ImGui::EndMenu();
							}
						}

						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Minimap"))
					{
						ImGui::Checkbox("Track enemies", &visuals->track_enemies);
						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}

			ImGui::Separator();

			if (ImGui::BeginMenu("Debug"))
			{
				if (ImGui::BeginMenu("Memory Viewer"))
				{
					ImGui::Text("Base: %llX", memory.base);
					ImGui::Text("Gadget: %llX", memory.gadget);
					ImGui::Text("Viewport: %u x %u", memory.viewport_width, memory.viewport_height);
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Players"))
				{
					ImGui::Text("Allies:");
					ImGui::Separator();
					for (auto& ally : memory.allies)
					{
						ImGui::Text("%s (%llX)", ally.hero_name().c_str(), ally.address());
						ImGui::Separator();
					}

					ImGui::Text("Enemies:");
					ImGui::Separator();
					for (auto& enemy : memory.enemies)
					{
						ImGui::Text("%s (%llX)", enemy.hero_name().c_str(), enemy.address());
						ImGui::Separator();
					}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Spells"))
				{
					Player& local = memory.allies.front();
					ImGui::Text("%s spells (%i):", local.hero_name(), local.spells.size());
					for (PlayerSpell& spell : local.spells)
					{
						ImGui::Text("%s", spell.name.c_str());
						ImGui::Text("Type: %s", spell.type.c_str());
						ImGui::Separator();
					}
					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			ImGui::End();
		}
	}
};

inline Menu menu;

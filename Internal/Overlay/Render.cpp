#include "Render.h"

void Render::overlay()
{
	ImGuiIO io = ImGui::GetIO();
	ImGui::SetNextWindowSize(io.DisplaySize);
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin(("##overlay"), nullptr,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_NoBackground
	);
	draw_list = ImGui::GetWindowDrawList();
	ImGui::End();
}

void Render::text(Vector2 position, std::string text, ImColor color, bool center, bool outline)
{
	if (center)
	{
		ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, 0.0f, text.c_str());
		position.x -= textSize.x / 2.0f;
	}

	if (outline)
	{
		ImColor black = ImColor(0.f, 0.f, 0.f, color.Value.w);
		draw_list->AddText(ImVec2(position.x + 1, position.y + 1), black, text.c_str());
		draw_list->AddText(ImVec2(position.x - 1, position.y - 1), black, text.c_str());
		draw_list->AddText(ImVec2(position.x + 1, position.y - 1), black, text.c_str());
		draw_list->AddText(ImVec2(position.x - 1, position.y + 1), black, text.c_str());
	}

	draw_list->AddText(ImVec2(position.x, position.y), color, text.c_str());
}

void Render::line(Vector2 start_position, Vector2 end_position, ImColor color, float thickness)
{
	draw_list->AddLine(ImVec2(start_position.x, start_position.y), ImVec2(end_position.x, end_position.y), color, thickness);
}

void Render::rect(Vector2 position, Vector2 size, ImColor color, float thickness, float rounding)
{
	draw_list->AddRect(ImVec2(position.x, position.y), ImVec2(size.x, size.y), color, rounding, 15, thickness);
}

void Render::filled_rect(Vector2 position, Vector2 size, ImColor color, float thickness, float rounding)
{
	draw_list->AddRectFilled(ImVec2(position.x, position.y), ImVec2(position.x + size.x, position.y + size.y), color, rounding, 15);
}

void Render::circle(Vector2 position, ImColor color, float radius, int segments)
{
	draw_list->AddCircle(ImVec2(position.x, position.y), radius, color, segments);
}

void Render::filled_circle(Vector2 position, ImColor color, float radius, int segments)
{
	draw_list->AddCircleFilled(ImVec2(position.x, position.y), radius, color, segments);
}

void Render::triangle(Vector2 point_a, Vector2 point_b, Vector2 point_c, ImColor color, float thickness)
{
	draw_list->AddTriangle(ImVec2(point_a.x, point_a.y), ImVec2(point_b.x, point_b.y), ImVec2(point_c.x, point_c.y), color, thickness);
}

void Render::filled_triangle(Vector2 point_a, Vector2 point_b, Vector2 point_c, ImColor color)
{
	draw_list->AddTriangleFilled(ImVec2(point_a.x, point_a.y), ImVec2(point_b.x, point_b.y), ImVec2(point_c.x, point_c.y), color);
}

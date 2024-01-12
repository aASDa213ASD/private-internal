#include "Render.h"

#include "../Common/WorldToScreen.h"

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

void Render::circle_w2s(const Vector3& world_position, ImColor color, float radius, int segments, float thickness, float glow)
{
	/*
	if (segments >= 200)
		return;

	static ImVec2 points[200];
	Vector3 worldSpace;
	Vector2 screenSpace;

	float step = 6.2831f / segments; // PI * 2
	float theta = 0.f;

	ImColor colors[200];

	for (int i = 0; i < segments; i++, theta += step) {
		worldSpace = { world_position.x + radius * cos(theta), world_position.y, world_position.z - radius * sin(theta) };
		screenSpace = WorldToScreen(worldSpace);

		// Calculate gradient color based on theta (angle)
		float hue = theta / (2 * 3.14159); // Normalize angle to [0, 1]
		colors[i] = ImColor::HSV(hue, 1.f, 1.f); // Create color from HSV values

		points[i].x = screenSpace.x;
		points[i].y = screenSpace.y;
	}

	draw_list->_FringeScale = 5.0f;

	for (int i = 0; i < segments - 1; ++i) {
		draw_list->AddLine(points[i], points[i + 1], colors[i], thickness);
	}

	draw_list->AddLine(points[segments - 1], points[0], colors[segments - 1], thickness);

	draw_list->_FringeScale = 1.0f;
	
	draw_list->_FringeScale = 10.0f;
	draw_list->AddPolyline(points, segments, color, true, thickness);
	draw_list->_FringeScale = 1.0f;
	
	*/

	if (segments > 200)
		return;

	Vector3 world_space;
	Vector2 screen_space;
	static ImVec2 points[200];
	const float angle_step = (M_PI * 2) / segments;
	float angle = 0.f;

	for (int i = 0; i < segments; i++, angle += angle_step) {
		world_space = { world_position.x + radius * cos(angle), world_position.y, world_position.z - radius * sin(angle) };
		screen_space = world_to_screen(world_space);

		points[i].x = screen_space.x;
		points[i].y = screen_space.y;
	}

	if (glow > 1.f)
	{
		ImColor glow_color = color;
		glow_color.Value.w = 0.3f;

		draw_list->_FringeScale = glow;
		draw_list->AddPolyline(points, segments, glow_color, true, thickness);
		draw_list->_FringeScale = 1.f;
	}

	draw_list->AddPolyline(points, segments, color, true, thickness);
}

void Render::filled_circle_w2s(const Vector3& world_position, ImColor color, float radius, int segments, float thickness)
{
	if (segments > 200)
		return;

	ImVec2 vertices[200];
	Vector3 vertices_2[200];
	bool vertices_valid[200];

	float angle = 0;
	const float angle_step = (M_PI * 2) / segments;

	for (int i = 0; i <= segments; ++i, angle += angle_step)
	{
		Vector3 pos = Vector3(radius * cosf(angle) + world_position.x, world_position.y, radius * sinf(angle) + world_position.z);
		Vector2 w2s_pos = world_to_screen(pos);
		vertices_valid[i] = w2s_pos.x > 0 && w2s_pos.x < memory.viewport_width && w2s_pos.y > 0 && w2s_pos.y < memory.viewport_height;
		vertices[i] = ImVec2(w2s_pos.x, w2s_pos.y);
		vertices_2[i] = Vector3(w2s_pos.x, w2s_pos.y, 0);
	}

	for (int i = 0; i < segments; ++i)
	{
		if (vertices_2[i].Distance(vertices_2[i + 1]) > radius)
			return;
	}

	draw_list->AddConvexPolyFilled(vertices, segments, color);
}

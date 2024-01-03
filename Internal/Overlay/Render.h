#pragma once

#include <string>
#include <vector>

#include "../Library/imgui/imgui.h"
#include "../Library/imgui/imgui_internal.h"
#include "../Library/vector/Vector2.h"
#include "../Library/vector/Vector3.h"

class Render {
private:
	ImDrawList* draw_list;

public:
	void overlay();
	void text(Vector2 position, std::string text, ImColor color = ImColor(1.f, 1.f, 1.f, 1.f), bool center = false, bool outline = false);
	void line(Vector2 start_position, Vector2 end_position, ImColor color = ImColor(0.f, 0.f, 0.f, 1.f), float thickness = 1.f);
	void rect(Vector2 position, Vector2 size, ImColor color = ImColor(0.f, 0.f, 0.f, 1.f), float thickness = 1.f, float rounding = 0.f);
	void filled_rect(Vector2 position, Vector2 size, ImColor color = ImColor(0.f, 0.f, 0.f, 1.f), float thickness = 1.f, float rounding = 0.f);
	void circle(Vector2 position, ImColor color = ImColor(1.f, 1.f, 1.f, 1.f), float radius = 0.f, int segments = 0);
	void filled_circle(Vector2 position, ImColor color = ImColor(1.f, 1.f, 1.f, 1.f), float radius = 0.f, int segments = 0);
	void triangle(Vector2 point_a, Vector2 point_b, Vector2 point_c, ImColor color = ImColor(1.f, 1.f, 1.f, 1.f), float thickness = 1.f);
	void filled_triangle(Vector2 point_a, Vector2 point_b, Vector2 point_c, ImColor color = ImColor(1.f, 1.f, 1.f, 1.f));
	void polygon(std::vector<Vector3> polygon);
	void circle_w2s(const Vector3& world_position, ImColor color = ImColor(1.f, 1.f, 1.f, 1.f), float radius = 0, int segments = 0, float thickness = 3.f);
	
	std::string spell = "No spell";
};

inline Render render;
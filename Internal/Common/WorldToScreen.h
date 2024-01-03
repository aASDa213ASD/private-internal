#pragma once

#include "../Library/matrix/Matrix4x4.h"
#include "../Library/vector/Vector2.h"
#include "../Library/vector/Vector3.h"

#include "../Common/Memory.h"
#include "../Offsets/World.h"

static Vector2 WorldToScreen(const Vector3& pos)
{
	Matrix4x4 view_matrix		= *reinterpret_cast<Matrix4x4*>(memory.base + oViewProjMatrices);
	Matrix4x4 projection_matrix	= *reinterpret_cast<Matrix4x4*>(memory.base + oViewProjMatrices + 0x40);
	Matrix4x4 view_proj_matrix	= Matrix4x4::Multiply(view_matrix, projection_matrix);

	Vector2 return_vec = { 0.f, 0.f };

	Vector4 clip_coords;
	clip_coords.x = pos.x * view_proj_matrix.matrix[0] \
				  + pos.y * view_proj_matrix.matrix[4] \
				  + pos.z * view_proj_matrix.matrix[8] \
				  + view_proj_matrix.matrix[12];

	clip_coords.y = pos.x * view_proj_matrix.matrix[1] \
				  + pos.y * view_proj_matrix.matrix[5] \
				  + pos.z * view_proj_matrix.matrix[9] \
				  + view_proj_matrix.matrix[13];

	clip_coords.z = pos.x * view_proj_matrix.matrix[2] \
				  + pos.y * view_proj_matrix.matrix[6] \
				  + pos.z * view_proj_matrix.matrix[10]\
				  + view_proj_matrix.matrix[14];

	clip_coords.w = pos.x * view_proj_matrix.matrix[3] \
				  + pos.y * view_proj_matrix.matrix[7] \
				  + pos.z * view_proj_matrix.matrix[11]\
				  + view_proj_matrix.matrix[15];

	if (clip_coords.w < 0.1f)
		return return_vec;

	Vector3 M;
	M.x = clip_coords.x / clip_coords.w;
	M.y = clip_coords.y / clip_coords.w;
	M.z = clip_coords.z / clip_coords.w;

	return_vec.x = (memory.viewport_width / 2.f * M.x) + (M.x + memory.viewport_width / 2.f);
	return_vec.y = -(memory.viewport_height / 2.f * M.y) + (M.y + memory.viewport_height / 2.f);

	return return_vec;
}
#pragma once
#include "Globals.h"
#include "vector.h"
#include <Windows.h>
#include "World.h"
void MultiplyMatrices(float* out, float* a, int row1, int col1, float* b, int row2, int col2);
void LoadW2S(uint64_t Base);
Vector2 WorldToScreen(Vector3 pos);
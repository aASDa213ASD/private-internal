#pragma once

#include <Windows.h>
#include <vector>
#include <format>

uint64_t GetAddressFromSignature(const std::vector<int> signature, uint64_t startaddress, uint64_t endaddress);
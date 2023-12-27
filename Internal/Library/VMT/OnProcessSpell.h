#pragma once

#include <Windows.h>

#include "../../Common/Globals.h"

void __fastcall on_cast(void* this_ptr, void* state, void* spell_cast_info) noexcept
{
    static auto fn = reinterpret_cast<void(__fastcall*)(void*, void*, void*)>(globals::vmt_ops);
    Beep(523, 500);
    return fn(this_ptr, state, spell_cast_info);
}
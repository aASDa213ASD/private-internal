#include "Evade.h"

#include <sstream>
#include <iomanip>

#include "../../Common/Memory.h"
#include "../../Library/VMT/VMTHook.h"
#include "../../Offsets/Objects.h"
#include "../../Offsets/Functions.h"
#include "../../Overlay/Render.h"
#include "Spell/Spell.h"
#include <format>

void Evade::load()
{
	thread_on_process_spell();
}

void Evade::update() {}

void Evade::unload() {}

void __fastcall on_cast(void* this_ptr, void* state, void* spell_cast_info) noexcept
{
	static auto fn = reinterpret_cast<void(__fastcall*)(void*, void*, void*)>(memory.vmt_on_process_spell);

	if (!spell_cast_info)
		return fn(this_ptr, state, spell_cast_info);

	/*
	std::stringstream ss;
	ss << std::hex << "This Pointer: 0x" << (reinterpret_cast<uint64_t>(this_ptr) - OnProcessSpellCast);
	render.spell = ss.str();
	*/

	Spell current_spell;
	current_spell.start_pos = *reinterpret_cast<Vector3*>((uint64_t)spell_cast_info + SpellCastStart);
	current_spell.end_pos = *reinterpret_cast<Vector3*>((uint64_t)spell_cast_info + SpellCastEnd);
	current_spell.cast_time = *reinterpret_cast<float*>((uint64_t)spell_cast_info + SpellCastCastTime);
	current_spell.cast_start = *reinterpret_cast<float*>((uint64_t)spell_cast_info + SpellCastStartTime);
	current_spell.cast_end = *reinterpret_cast<float*>((uint64_t)spell_cast_info + SpellCastCastTimeEnd);
	current_spell.slot = *reinterpret_cast<int*>((uint64_t)spell_cast_info + SpellCastSpellSlot);

	uint64_t _nameaddr = *reinterpret_cast<uint64_t*>(spell_cast_info);
	
	if (_nameaddr)
	{
		uint64_t __nameaddr = *reinterpret_cast<uint64_t*>(_nameaddr + 0x18);
		if (__nameaddr)
		{
			uint64_t nameaddr = *reinterpret_cast<uint64_t*>(__nameaddr + 0x8);

			if (nameaddr)
			{
				char* _name = reinterpret_cast<char*>(nameaddr);
				if (_name)
				{
					for (int i = 0; i < 45 && std::isalpha(_name[i]); ++i)
					{
						current_spell.name.push_back(_name[i]);
					}
				}
			}
		}	
	}

	if (current_spell.name.find("Attack") != std::string::npos)
		return fn(this_ptr, state, (void*)spell_cast_info);
	
	for (auto& ally : memory.allies)
	{
		if (ally.address() == (reinterpret_cast<uint64_t>(this_ptr) - OnProcessSpellCast))
		{
			render.spell = std::format("Spell {} casted by {}", current_spell.name, ally.hero_name());

			for (auto& spell : ally.spells)
			{
				if (current_spell.name == spell.name)
				{
					/* Getting data from SpellDB of a player and assign to current_spell */
					current_spell.missile_width = spell.missile_width;
					/* Adding current_spell to active_missiles vector */
					memory.active_missiles.push_back(current_spell);
				}
			}

			break;
		}
	}
	
	return fn(this_ptr, state, spell_cast_info);
}

void WINAPI on_process_spell()
{
	VMTHook VMTHOnProcessSpellCast[10];
	uint64_t _l = *reinterpret_cast<uint64_t*>(memory.base + LocalPlayer);

	memory.vmt_on_process_spell = VMTHOnProcessSpellCast[0].Hook(
		reinterpret_cast<void*>(static_cast<uint64_t>(_l + OnProcessSpellCast)), 29,
		reinterpret_cast<uintptr_t>(&on_cast)
	);

	while (true) {
		Sleep(1000);
	}
}

void Evade::thread_on_process_spell()
{
	DWORD  process_id     = GetCurrentProcessId();
	HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
	PVOID  remote_memory  = VirtualAllocEx(process_handle, nullptr, 0x45, MEM_COMMIT, PAGE_READWRITE);
	DWORD  thread_id;

	HANDLE RemoteThread = CreateRemoteThread(
		process_handle, nullptr, 0,
		reinterpret_cast<LPTHREAD_START_ROUTINE>(on_process_spell),
		remote_memory, 0, &thread_id
	);
}


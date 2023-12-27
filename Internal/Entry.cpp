#pragma warning (disable : 6387)

#include <Windows.h>
#include <thread>

#include "Hooks.h"
#include "Common/Globals.h"
#include "Common/Spoof.h"
#include "Library/VMT/VMTHook.h"
#include "Library/VMT/OnProcessSpell.h"
#include "Offsets/Objects.h"

bool WINAPI HideThread(const HANDLE hThread) noexcept
{
	__try {
		using FnSetInformationThread = NTSTATUS(NTAPI*)(
			HANDLE ThreadHandle, UINT ThreadInformationClass,
			PVOID ThreadInformation, ULONG ThreadInformationLength
		);

		const auto NtSetInformationThread { 
			reinterpret_cast<FnSetInformationThread>(
				::GetProcAddress(::GetModuleHandleW(L"ntdll.dll"), "NtSetInformationThread")
		) };

		if (!NtSetInformationThread)
			return false;

		if (const auto status { NtSetInformationThread(hThread, 0x11u, nullptr, 0ul) }; status == 0x00000000)
			return true;
	}
	__except (TRUE) {
		return false;
	}

	return false;
}

void WINAPI _OnProcessSpell()
{
	VMTHook VMTHOnProcessSpellCast[10];
	uint64_t _l = *reinterpret_cast<uint64_t*>(globals::base + LocalPlayer);

	globals::vmt_ops = VMTHOnProcessSpellCast[0].Hook(
		reinterpret_cast<void*>(static_cast<uint64_t>(_l + 0x11b8)), 29,
		reinterpret_cast<uintptr_t>(&on_cast)
	);

	while (true) {
		Sleep(1000);
	}
}

void t_OnProcessSpell()
{
	DWORD  process_id     = GetCurrentProcessId();
	HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
	PVOID  remote_memory  = VirtualAllocEx(process_handle, nullptr, 0x45, MEM_COMMIT, PAGE_READWRITE);
	DWORD  thread_id;

	HANDLE RemoteThread = CreateRemoteThread(
		process_handle, nullptr, 0,
		reinterpret_cast<LPTHREAD_START_ROUTINE>(_OnProcessSpell),
		remote_memory, 0, &thread_id
	);
}

__declspec(safebuffers) static void WINAPI DllAttach([[maybe_unused]] LPVOID lp) noexcept
{
	globals::base = reinterpret_cast<std::uintptr_t>(::GetModuleHandle(nullptr));
	globals::gadget = GetAddressFromSignature({ 0xff, 0x23 }, globals::base, 0xffffffffffff);

	//t_OnProcessSpell();
	hooks.install();

	Beep(523, 500);
}

__declspec(safebuffers) static void WINAPI DllDetach([[maybe_unused]] LPVOID lp) noexcept
{
	hooks.uninstall();
	VirtualFree(reinterpret_cast<void*>(::GetModuleHandle(nullptr)), 0, MEM_RELEASE);

	Beep(523, 500);
}

__declspec(safebuffers) BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD reason, [[maybe_unused]] LPVOID reserved)
{
	DisableThreadLibraryCalls(hModule);
	HideThread(hModule);

	if (reason == DLL_PROCESS_ATTACH)
	{
		::_beginthreadex(
			nullptr, 0u,
			reinterpret_cast<_beginthreadex_proc_type>(DllAttach),
			nullptr, 0u, nullptr
		);
	}

	else if (reason == DLL_PROCESS_DETACH)
	{
		::_beginthreadex(
			nullptr, 0u,
			reinterpret_cast<_beginthreadex_proc_type>(DllDetach),
			nullptr, 0u, nullptr
		);
	}

	::CloseHandle(hModule);

	return TRUE;
}
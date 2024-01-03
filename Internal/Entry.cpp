#pragma warning (disable : 6387)

#include <Windows.h>
#include <thread>

#include "Hooks.h"
#include "Common/Memory.h"
#include "Features/Featurectl.h"
#include "Features/Evade/Evade.h"
#include "Offsets/Objects.h"
#include "Features/SkinChanger/SkinChanger.h"
#include "Features/Visuals/Visuals.h"

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

__declspec(safebuffers) static void WINAPI DllAttach([[maybe_unused]] LPVOID lp) noexcept
{
	memory.initialize();

	//featurectl.load_feature(std::make_unique<Evade>());
	featurectl.load_feature(std::make_unique<SkinChanger>());
	//featurectl.load_feature(std::make_unique<Visuals>());

	hooks.install();

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

	::CloseHandle(hModule);

	return TRUE;
}
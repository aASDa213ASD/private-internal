#pragma warning (disable : 6387)

#include <Windows.h>
#include <thread>

#include "Hooks.h"

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
	hooks.install();
}

__declspec(safebuffers) BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD reason, [[maybe_unused]] LPVOID reserved)
{
	DisableThreadLibraryCalls(hModule);

	if (reason != DLL_PROCESS_ATTACH)
		return FALSE;

	HideThread(hModule);

	::_beginthreadex(
		nullptr, 0u,
		reinterpret_cast<_beginthreadex_proc_type>(DllAttach),
		nullptr, 0u, nullptr
	);
	
	::CloseHandle(hModule);

	return TRUE;
}

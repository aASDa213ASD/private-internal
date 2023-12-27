#include "DLC.h"

#include <fstream>

#include "LazyImport.h"

#include "../Interface/GUI.h"
#include "../Common/Loader.h"

NTSTATUS NTAPI NtCreateThreadEx(PHANDLE, ACCESS_MASK, LPVOID, HANDLE, LPTHREAD_START_ROUTINE, LPVOID, BOOL, SIZE_T, SIZE_T, SIZE_T, LPVOID);

bool DLC::load_library(HANDLE process_handle, const wchar_t* dll_file_path, const wchar_t* dll_file_name)
{
	if (!process_handle || process_handle == INVALID_HANDLE_VALUE)
		return false;

	const auto dll_path{ std::wstring(dll_file_path) + dll_file_name };

	if (const auto f{ std::ifstream(dll_path) }; !f.is_open()) {
		gui.terminal_write("Couldn't find injectable dll.");
		LI_FN(CloseHandle)(process_handle);
		return false;
	}

	const auto dll_path_remote{
		LI_FN(VirtualAllocEx).get()(
		process_handle, nullptr, (dll_path.size() + 1) * sizeof(wchar_t),
		MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE
	) };

	if (!dll_path_remote) {
		gui.terminal_write("Fatal on memory allocation.");
		LI_FN(CloseHandle)(process_handle);
		return false;
	}

	if (!LI_FN(WriteProcessMemory).get()(process_handle, dll_path_remote, dll_path.data(), (dll_path.size() + 1) * sizeof(wchar_t), nullptr)) {
		gui.terminal_write("Fatal on memory write.");
		LI_FN(VirtualFreeEx).get()(process_handle, dll_path_remote, 0u, MEM_RELEASE);
		LI_FN(CloseHandle)(process_handle);
		return false;
	}

	HANDLE thread{};
	LI_FN(NtCreateThreadEx).nt_cached()(
		&thread, GENERIC_ALL, nullptr, process_handle,
		reinterpret_cast<LPTHREAD_START_ROUTINE>(LI_FN(GetProcAddress).get()(LI_FN(GetModuleHandleW).get()(L"kernel32.dll"), "LoadLibraryW")),
		dll_path_remote, FALSE, NULL, NULL, NULL, nullptr
		);

	if (!thread || thread == INVALID_HANDLE_VALUE) {
		gui.terminal_write("Fatal on thread creation.");
		LI_FN(VirtualFreeEx).get()(process_handle, dll_path_remote, 0u, MEM_RELEASE);
		LI_FN(CloseHandle)(process_handle);
		return false;
	}

	LI_FN(WaitForSingleObject)(thread, INFINITE);
	LI_FN(CloseHandle)(thread);
	LI_FN(VirtualFreeEx).get()(process_handle, dll_path_remote, 0u, MEM_RELEASE);
	LI_FN(CloseHandle)(process_handle);

	return true;
}

void DLC::inject()
{
	target_pid = find_process_id(target_process);
	if (!target_pid)
	{
		loader.set_status("No target found.");
		return;
	}

	HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, target_pid);
	if (!process_handle)
	{
		loader.set_status("Process open failed.");
		return;
	}

	if (!load_library(process_handle, loader.current_directory, loader.target_dllw))
	{
		loader.set_status("Fatal on LoadLibrary.");
		CloseHandle(process_handle);
		return;
	}

	CloseHandle(process_handle);

	loader.connect(target_pid);
}

DWORD DLC::find_process_id(const char* process_name)
{
	PROCESSENTRY32 process_entry{ 0 };
	process_entry.dwSize = sizeof(process_entry);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE)
		gui.terminal_write("Snapshot (TL32) creation failed.");

	DWORD PID = 0;
	bool process = Process32First(snapshot, &process_entry);

	while (process)
	{
		if (!strcmp(process_name, process_entry.szExeFile))
		{
			PID = process_entry.th32ProcessID;
			break;
		}
		process = Process32Next(snapshot, &process_entry);
	}

	if (snapshot)
		CloseHandle(snapshot);

	return PID;
}

uintptr_t DLC::get_module_base(DWORD process_id, const char* module_name)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do {
				if (!_stricmp(modEntry.szModule, module_name))
				{
					CloseHandle(hSnap);
					return (uintptr_t)modEntry.modBaseAddr;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}

	CloseHandle(hSnap);
	return NULL;
}
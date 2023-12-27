#pragma once

#include <Windows.h>
#include <TlHelp32.h>

class DLC {
private:
	const char* target_process = "League of Legends.exe";
	DWORD target_pid = 0;

	bool load_library(
		HANDLE process_handle,
		const wchar_t* dll_file_path,
		const wchar_t* dll_file_name
	);

public:
	DWORD find_process_id(const char* process_name);
	uintptr_t get_module_base(DWORD process_id, const char* module_name);
	void inject();
};

inline DLC dlc;
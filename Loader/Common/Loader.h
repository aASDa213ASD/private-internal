#pragma once

#include <Windows.h>
#include <iostream>
#include <filesystem>

class Loader {
private:
	HANDLE m_loader_mutex = nullptr;

public:
	struct Settings {
		bool auto_inject  = false;
		bool auto_rename  = false;
		bool stream_proof = true;
	} settings;

	struct Mode {
		const char* str = "Manual";
	} mode;

	struct Connection {
		bool current = false;
		const char* str = "";
		DWORD attached_process_id = 0;
	} connection;

	std::string status;

	std::vector<std::wstring> dll_namesw;
	std::vector<std::string>  dll_names;

	const wchar_t* target_dllw = nullptr;
	const char* target_dll = nullptr;

	const wchar_t* current_directory = L"";

	int initialize();
	int destroy();
	void connect(DWORD process_id);
	void disconnect();
	void run();
	void auto_inject();
	bool is_already_running();
	void set_window_affinity();
	void set_status(const char* text, ...);
	void find_dll_files();
	const wchar_t* get_current_directory(
		const std::wstring& file_path
	);

};

inline Loader loader;
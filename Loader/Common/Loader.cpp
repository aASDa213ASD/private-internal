#include "Loader.h"

#include <tlhelp32.h>
#include <thread>
#include <chrono>
#include <future>
#include <psapi.h>

#include "../Interface/GUI.h"
#include "../DLC/DLC.h"

void Loader::run()
{
	float game_time;
	uintptr_t base_address;
	uintptr_t game_time_offset = 0x2226D48;

	while (true)
	{
		if (!settings.auto_inject)
		{
			std::this_thread::sleep_for(std::chrono::seconds(5));
			continue;
		}

		DWORD target_pid = dlc.find_process_id("League of Legends.exe");
		if (!target_pid)
		{
			loader.disconnect();
			std::this_thread::sleep_for(std::chrono::seconds(1));
			continue;
		}

		HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, target_pid);
		if (!process_handle)
		{
			continue;
		}

		base_address = dlc.get_module_base(target_pid, "League of Legends.exe");
		if (ReadProcessMemory(process_handle, reinterpret_cast<void*>(base_address + game_time_offset), &game_time, sizeof(float), nullptr))
		{
			if (3 <= game_time)
			{
				CloseHandle(process_handle);
				dlc.inject();
			}
		}

		CloseHandle(process_handle);
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

int Loader::initialize()
{
	if (this->is_already_running())
	{
		::MessageBoxA(nullptr, "Already running. Cannot run multiple instances of the loader.", "Loader", MB_OK | MB_ICONINFORMATION);
		this->destroy();
		gui.is_running = false;
		return EXIT_FAILURE;
	}
	
	find_dll_files();

	std::thread(&Loader::run, this).detach();

	return EXIT_SUCCESS;
}

int Loader::destroy()
{
	ReleaseMutex(m_loader_mutex);
	CloseHandle(m_loader_mutex);
	return EXIT_SUCCESS;
}

void Loader::connect(DWORD process_id)
{
	connection.attached_process_id = process_id;
	connection.current = true;
	connection.str = "Attached";
}

void Loader::disconnect()
{
	connection.attached_process_id = 0;
	connection.current = false;
	connection.str = "Detached";
}

void Loader::set_window_affinity()
{
	SetWindowDisplayAffinity(gui.window, this->settings.stream_proof ? WDA_EXCLUDEFROMCAPTURE : WDA_NONE);
}

void Loader::set_status(const char* text, ...)
{
	va_list args;
	va_start(args, text);

	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), text, args);

	status.assign(buffer);

	va_end(args);
}

bool Loader::is_already_running()
{
	this->m_loader_mutex = CreateMutexA(nullptr, TRUE, "loader_mutex");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true;

	if (this->m_loader_mutex)
	{
		unsigned int waitResult = WaitForSingleObject(this->m_loader_mutex, NULL);
		if (waitResult != WAIT_OBJECT_0 && waitResult != WAIT_ABANDONED)
			return true;
	}

	return false;
}

const wchar_t* Loader::get_current_directory(const std::wstring &file_path)
{
	size_t lastSlash = file_path.find_last_of(L"\\/");

	if (lastSlash == std::string::npos)
		return _wcsdup(L"");

	if (lastSlash == 0)
		return _wcsdup(L"\\");

	std::wstring result = file_path.substr(0, lastSlash);
	current_directory = _wcsdup(result.c_str());
	return _wcsdup(result.c_str());
}

void Loader::find_dll_files()
{
	wchar_t buffer[MAX_PATH];
	GetModuleFileNameW(NULL, buffer, MAX_PATH);

	std::wstring path = get_current_directory(buffer);

	for (const auto &entry : std::filesystem::directory_iterator(path))
	{
		if (entry.is_regular_file() && entry.path().extension() == L".dll")
		{
			std::wstring dll_file_namew = L"\\" + entry.path().filename().wstring();
			dll_namesw.push_back(dll_file_namew);

			std::string dll_file_name = entry.path().filename().string();
			dll_names.push_back(dll_file_name);
		}
	}

	if (!dll_names.empty())
	{
		target_dllw = dll_namesw[0].c_str();
		target_dll = dll_names[0].c_str();
	}
}

void Loader::auto_inject()
{
	gui.terminal_write("Auto");
	std::this_thread::sleep_for(std::chrono::seconds(3));
}
#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <future>
#include <chrono>

#include "Interface/GUI.h"
#include "Common/Loader.h"

// TODO: Fully unload DLL from memory

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previousInstance, PWSTR arguments, int commandShow)
{
	loader.initialize();
	gui.initialize();
	loader.set_window_affinity();

	gui.run();
	loader.destroy();

	return EXIT_SUCCESS;
}

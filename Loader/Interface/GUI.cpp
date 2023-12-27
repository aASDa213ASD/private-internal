#include "GUI.h"

#include <iostream>
#include <filesystem>

#include "../Library/imgui/imgui.h"
#include "../Library/imgui/imgui_impl_dx11.h"
#include "../Library/imgui/imgui_impl_win32.h"
#include "../Common/Loader.h"
#include "../DLC/DLC.h"
#include "ImGui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wideParameter, LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{

	case WM_SIZE: {
		if (wideParameter == SIZE_MINIMIZED) {
			ShowWindow(gui.window, SW_HIDE);
		}
		else if (wideParameter == SIZE_RESTORED) {
			ShowWindow(gui.window, SW_SHOWNORMAL);
		}
	} break;

	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
	} break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	} return 0;

	case WM_LBUTTONDOWN: {
		gui.position = MAKEPOINTS(longParameter);
	} return 0;

	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(gui.window, &rect);

			rect.left += points.x - gui.position.x;
			rect.top += points.y - gui.position.y;

			if (gui.position.x >= 0 && gui.position.x <= gui.WIDTH && gui.position.y >= 0 && gui.position.y <= 19)
				SetWindowPos(
					gui.window, HWND_TOPMOST,
					rect.left, rect.top, 0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}
	} return 0;

	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}

void GUI::create_window(const char* windowName) noexcept
{
	window_class.cbSize = sizeof(WNDCLASSEX);
	window_class.style = CS_CLASSDC;
	window_class.lpfnWndProc = WindowProcess;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = GetModuleHandleA(0);
	window_class.hIcon = 0;
	window_class.hCursor = 0;
	window_class.hbrBackground = 0;
	window_class.lpszMenuName = 0;
	window_class.lpszClassName = "class001";
	window_class.hIconSm = 0;

	RegisterClassEx(&window_class);

	window = CreateWindowEx(
		0, "class001", windowName, WS_POPUP,
		100, 100,
		WIDTH, HEIGHT,
		0,0, window_class.hInstance, 0
	);

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void GUI::destroy_window() noexcept
{
	DestroyWindow(window);
	UnregisterClass(window_class.lpszClassName, window_class.hInstance);
}

bool GUI::create_render_target() noexcept
{
	ID3D11Texture2D* pBackBuffer;
	if (S_OK != swap_chain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)))
		return false;
	if (S_OK != d3d_device->CreateRenderTargetView(pBackBuffer, nullptr, &d3d_render_target))
		return false;
	pBackBuffer->Release();
	return true;
}

void GUI::cleanup_render_target() noexcept
{
	if (d3d_render_target)
	{
		d3d_render_target->Release();
		d3d_render_target = nullptr;
	}
}

bool GUI::create_device() noexcept
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = window;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	/* createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; */
	D3D_FEATURE_LEVEL featureLevel;
	constexpr D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (constexpr UINT createDeviceFlags = 0; D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags,
		featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &swap_chain,
		&d3d_device, &featureLevel, &d3d_context) != S_OK)
		return false;

	if (!create_render_target())
		return false;

	return true;
}

void GUI::destroy_device() noexcept
{
	cleanup_render_target();

	if (swap_chain)
	{
		swap_chain->Release();
		swap_chain = nullptr;
	}

	if (d3d_context)
	{
		d3d_context->Release();
		d3d_context = nullptr;
	}

	if (d3d_device)
	{
		d3d_device->Release();
		d3d_device = nullptr;
	}
}

void GUI::create_imgui() noexcept
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ::ImGui::GetIO();

	io.IniFilename = NULL;

	// ImGui::StyleColorsDark(); // Change to color initializations
	set_imgui_style();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(d3d_device, d3d_context);
}

void GUI::set_imgui_style() noexcept
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.5f;
	style.WindowPadding = ImVec2(12.0f, 12.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(20.0f, 20.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_None;
	style.ChildRounding = 4.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(6.0f, 6.0f);
	style.FrameRounding = 4.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(6.0f, 6.0f);
	style.ItemInnerSpacing = ImVec2(6.0f, 3.0f);
	style.CellPadding = ImVec2(8.0f, 6.0f);
	style.IndentSpacing = 20.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 4.0f;
	style.GrabMinSize = 12.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5372549295425415f, 0.5529412031173706f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.733905553817749f, 0.7338982224464417f, 0.733902633190155f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.8540772199630737f, 0.9417561292648315f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(9.999911299019004e-07f, 9.999899930335232e-07f, 9.999999974752427e-07f, 0.501960813999176f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(9.99991698336089e-07f, 9.999899930335232e-07f, 9.999999974752427e-07f, 0.501960813999176f);
}

void GUI::destroy_imgui() noexcept
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void GUI::start_frame() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			is_running = !is_running;
			return;
		}
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void GUI::end_frame() noexcept
{
	auto clear_color = ImVec4(0, 0, 0, 255.f);
	ImGui::EndFrame();
	ImGui::Render();
	d3d_context->OMSetRenderTargets(1, &d3d_render_target, nullptr);
	d3d_context->ClearRenderTargetView(d3d_render_target, reinterpret_cast<float*>(&clear_color));
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	/* swap_chain->Present(0, 0); // Present without vsync */
	swap_chain->Present(1, 0); // Present with vsync
}

void GUI::render() noexcept
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize(ImVec2(static_cast<float>(WIDTH), static_cast<float>(HEIGHT)));

	ImGui::Begin(
		"Loader",
		&is_running,
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize
	);

	if (ImGui::BeginTabBar("tabs"))
	{
		if (ImGui::BeginTabItem("Loader"))
		{
			ImGui::BeginGroup();

			if (loader.settings.auto_inject)
				ImGui::BeginDisabled();
			if (ImGui::Button("Load", ImVec2(300.0f, 116.0f)))
				dlc.inject();
			if (loader.settings.auto_inject)
				ImGui::EndDisabled();

			ImGui::BeginDisabled();
			ImGui::Button("Unload", ImVec2(300.0f, 116.0f));
			ImGui::EndDisabled();

			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();

			if (ImGui::BeginChild("Status", ImVec2(270, 240), true))
			{
				loader.connection.str = loader.connection.current ? "Attached" : "Detached";
				loader.mode.str = loader.settings.auto_inject ? "Auto" : "Manual";

				ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - ImGui::CalcTextSize(loader.connection.str).x) * 0.5f, ImGui::GetWindowSize().y * 0.45f));

				ImVec4 color = loader.connection.current ? ImVec4(0.3960f, 1.0f, 0.6120f, 1.0f) : ImVec4(1.0f, 0.3960f, 0.3960f, 1.0f);
				ImGui::TextColored(color, loader.connection.str);

				ImGui::EndChild();
			}

			ImGui::EndGroup();

			ImGui::Separator();

			ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 25);
			ImGui::Text(loader.status.c_str());
		
			ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - ImGui::CalcTextSize(loader.mode.str).x) - 20, ImGui::GetWindowSize().y - 25));
			ImGui::Text(loader.mode.str);
			ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - ImGui::CalcTextSize(loader.target_dll).x) - 80, ImGui::GetWindowSize().y - 25));
			ImGui::Text(loader.target_dll);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Terminal"))
		{
			std::string text;
			for (const auto& line : terminal_lines) {
				text += line + "\n";
			}

			ImGui::InputTextMultiline("##ConsoleText", (char*)text.c_str(), text.size() + 1,
				ImVec2(-1.0f, -1.0f), ImGuiInputTextFlags_ReadOnly);
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Settings"))
		{
			if (loader.settings.auto_inject)
				ImGui::BeginDisabled();

			if (ImGui::BeginCombo("##injectable", loader.target_dll))
			{
				for (size_t i = 0; i < loader.dll_names.size(); ++i)
				{
					bool is_selected = (loader.target_dll != nullptr && std::strcmp(loader.target_dll, loader.dll_names[i].c_str()) == 0);
					if (ImGui::Selectable(loader.dll_names[i].c_str(), is_selected))
					{
						loader.target_dllw = loader.dll_namesw[i].c_str();
						loader.target_dll = loader.dll_names[i].c_str();
						gui.terminal_write("New target set: %s", loader.target_dll);
					}

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			if (loader.settings.auto_inject)
				ImGui::EndDisabled();

			ImGui::Separator();

			ImGui::Checkbox("Auto inject", &loader.settings.auto_inject);
			ImGui::Helpmark("Automatically inject on new game instance.");
			ImGui::SameLine();
			ImGui::BeginDisabled();
			ImGui::Checkbox("Auto rename", &loader.settings.auto_rename);
			ImGui::Helpmark("Rename loader executable on launch.");
			ImGui::EndDisabled();

			ImGui::Separator();

			if (ImGui::Checkbox("Stream proof", &loader.settings.stream_proof))
				loader.set_window_affinity();
			ImGui::Helpmark("Hide loader from recording software.");

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}

void GUI::terminal_write(const char* line, ...)
{
	va_list args;
	va_start(args, line);

	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), line, args);

	terminal_lines.push_back(buffer);

	va_end(args);
}

void GUI::initialize()
{
	create_window("Loader");
	create_device();
	create_imgui();
}

void GUI::run()
{
	while (is_running)
	{
		start_frame();
		render();
		end_frame();
	}

	destroy_imgui();
	destroy_device();
	destroy_window();
}
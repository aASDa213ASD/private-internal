#pragma once

#include <d3d11.h>
#include <vector>
#include <string>

class GUI {
private:
	WNDCLASSEX window_class = { };
	ID3D11Device* d3d_device = nullptr;
	IDXGISwapChain* swap_chain = nullptr;
	ID3D11DeviceContext* d3d_context = nullptr;
	ID3D11RenderTargetView* d3d_render_target = nullptr;

	std::vector<std::string> terminal_lines;

	void create_window(const char* windowName) noexcept;
	void destroy_window() noexcept;

	bool create_render_target() noexcept;
	void cleanup_render_target() noexcept;

	bool create_device() noexcept;
	void destroy_device() noexcept;

	void create_imgui() noexcept;
	void set_imgui_style() noexcept;
	void destroy_imgui() noexcept;

	void start_frame() noexcept;
	void end_frame() noexcept;
	void render() noexcept;

public:
	HWND window = nullptr;
	POINTS position = { };
	bool is_running = true;
	int WIDTH = 600;
	int HEIGHT = 350;

	void terminal_write(const char* line, ...);
	void initialize();
	void run();
};

inline GUI gui;

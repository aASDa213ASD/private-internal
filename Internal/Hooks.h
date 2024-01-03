#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <mutex>

#include "Features/Visuals/Visuals.h"

typedef HRESULT(__stdcall* Present) (
	IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags
);

typedef HRESULT(__stdcall* ResizeBuffer) (
	IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width,
	UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags
);

typedef LRESULT(CALLBACK* WNDPROC) (
	HWND, UINT, WPARAM, LPARAM
);

class Hooks {
public:
	Present present = nullptr;
	ResizeBuffer resize_buffer = nullptr;

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	ID3D11RenderTargetView* render_target_view = nullptr;

	HWND window = nullptr;
	WNDPROC window_procedure = nullptr;
	std::once_flag init_flag;

	Visuals* visuals;
	
	void install();
	void uninstall();
	void initialize(IDXGISwapChain* pSwapChain);
};

inline Hooks hooks;
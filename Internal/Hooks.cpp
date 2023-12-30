#include "Hooks.h"

#include "Library/kiero/kiero.h"
#include "Library/imgui/imgui.h"
#include "Library/imgui/imgui_impl_win32.h"
#include "Library/imgui/imgui_impl_dx11.h"

#include "Overlay/Menu.h"
#include "Overlay/Render.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall wndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	if (uMsg == WM_KEYDOWN)
	{
		if (wParam == VK_INSERT)
		{
			menu.is_opened = !menu.is_opened;
		}
	}

	return CallWindowProc(hooks.window_procedure, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall onPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{	
	std::call_once(hooks.init_flag, [&]() { hooks.initialize(pSwapChain); });

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	render.overlay();
	//render.text(Vector2(1000, 1000), render.spell, ImColor(1.0f, 1.0f, 1.0f, 1.0f), false, true);

	if (menu.is_opened)
		menu.render();

	ImGui::EndFrame();
	ImGui::Render();
	hooks.context->OMSetRenderTargets(1, &hooks.render_target_view, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return hooks.present(pSwapChain, SyncInterval, Flags);
}

HRESULT onResizeBuffer(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (&hooks.render_target_view) {
		hooks.context->OMSetRenderTargets(0, 0, 0);
		hooks.render_target_view->Release();
	}

	HRESULT hr = hooks.resize_buffer(
		pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags
	);

	ID3D11Texture2D* pBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);

	if (pBuffer)
	{
		hooks.device->CreateRenderTargetView(pBuffer, nullptr, &hooks.render_target_view);
		pBuffer->Release();
	}

	hooks.context->OMSetRenderTargets(1, &hooks.render_target_view, nullptr);

	D3D11_VIEWPORT vp = {
		0.0f, 0.0f,
		static_cast<FLOAT>(Width), static_cast<FLOAT>(Height),
		0.0f, 1.0f
	};

	hooks.context->RSSetViewports(1, &vp);
	return hr;
}

void Hooks::initialize(IDXGISwapChain* pSwapChain)
{
	if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device)))) {
		{
			hooks.device->GetImmediateContext(&hooks.context);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			hooks.window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));

			if (pBackBuffer)
			{
				hooks.device->CreateRenderTargetView(pBackBuffer, nullptr, &hooks.render_target_view);
				pBackBuffer->Release();
			}

			hooks.window_procedure = (WNDPROC)SetWindowLongPtr(hooks.window, GWLP_WNDPROC, (LONG_PTR)wndProc);

			ImGui::CreateContext();
			ImGui_ImplWin32_Init(hooks.window);
			ImGui_ImplDX11_Init(hooks.device, hooks.context);
			menu.aquire_styles();
		}
	}
}

void Hooks::install()
{
	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
		kiero::bind(8, reinterpret_cast<void**>(&present), onPresent);
		kiero::bind(13, reinterpret_cast<void**>(&resize_buffer), onResizeBuffer);
	}
}

void Hooks::uninstall()
{
	kiero::shutdown();
}

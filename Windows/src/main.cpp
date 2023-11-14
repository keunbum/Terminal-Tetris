#define NOMINMAX

#include <windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1")

#include <utility>

#include "basewin.h"

template <class T>
void SafeRelease(T** ppT)
{
	if (*ppT != nullptr)
	{
		(*ppT)->Release();
		*ppT = nullptr;
	}
}

class MainWindow : public BaseWindow<MainWindow>
{
private:
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrush;
	D2D1_ELLIPSE ellipse;

	void    CalculateLayout();
	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();
	void    OnPaint();
	void    Resize();

public:
	MainWindow() : pFactory(nullptr), pRenderTarget(nullptr), pBrush(nullptr), ellipse() {}

	PCWSTR  ClassName() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

// Recalculate drawing layout when the size of the window changes.

void MainWindow::CalculateLayout()
{
	if (pRenderTarget == nullptr)
	{
		return;
	}

	const D2D1_SIZE_F size = pRenderTarget->GetSize();
	const float x = size.width / 2;
	const float y = size.height / 2;
	const float radius = std::min(x, y);

	ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
}

HRESULT MainWindow::CreateGraphicsResources()
{
	if (pRenderTarget != nullptr)
	{
		return S_OK;
	}

	RECT rc{};
	GetClientRect(m_hwnd, &rc);

	const D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
	const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);

	HRESULT hr{};
	if (SUCCEEDED(hr = pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_hwnd, size),
		&pRenderTarget))
		&& SUCCEEDED(hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush)))
	{
		CalculateLayout();
	}

	return hr;
}

void MainWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrush);
}

void MainWindow::OnPaint()
{
	if (FAILED(CreateGraphicsResources()))
	{
		return;
	}

	PAINTSTRUCT ps{};
	BeginPaint(m_hwnd, &ps);

	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
	pRenderTarget->FillEllipse(ellipse, pBrush);
	HRESULT hr = pRenderTarget->EndDraw();
	if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
	{
		DiscardGraphicsResources();
	}

	EndPaint(m_hwnd, &ps);
}

void MainWindow::Resize()
{
	if (pRenderTarget == nullptr)
	{
		return;
	}

	RECT rc{};
	GetClientRect(m_hwnd, &rc);

	const D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
	pRenderTarget->Resize(size);

	CalculateLayout();
	InvalidateRect(m_hwnd, nullptr, FALSE);
}

int WINAPI wWinMain(
	_In_ HINSTANCE,
	_In_opt_ HINSTANCE,
	_In_ LPWSTR,
	_In_ int nShowCmd)
{
	MainWindow win;
	if (!win.Create(L"Circle Sample", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}
	ShowWindow(win.Window(), nShowCmd);

	// Run the message loop.
	BOOL res;
	MSG msg{};
	while ((res = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (res == -1)
	{
		// Handle some errors.
	}

	return 0;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&pFactory)))
		{
			return -1;  // Fail CreateWindowEx.
		}
		return 0;
	case WM_DESTROY:
		DiscardGraphicsResources();
		SafeRelease(&pFactory);
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		OnPaint();
		return 0;
		// Other messages not shown...
	case WM_SIZE:
		Resize();
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
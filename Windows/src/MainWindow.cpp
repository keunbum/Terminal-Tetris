#define NOMINMAX

#include <utility>

#include "MainWindow.h"

MainWindow::MainWindow() : mFactory(nullptr), mRenderTarget(nullptr), mBrush(nullptr), mRect() {}

LRESULT MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        return 0;
    case WM_DESTROY:
        discardGraphicsResources();
        util::SafeRelease(&mFactory);
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        onPaint();
        return 0;
    case WM_SIZE:
        resize();
        return 0;
    }
    return DefWindowProc(mHwnd, uMsg, wParam, lParam);
}

/* Recalculate drawing layout when the size of the window changes. */
void MainWindow::calculateLayout()
{
    if (mRenderTarget == nullptr)
    {
        return;
    }
    const D2D1_SIZE_F winSize = mRenderTarget->GetSize();
    const FLOAT x = 0.5F * winSize.width;
    const FLOAT y = 0.5F * winSize.height;
    const FLOAT sideHalf = 0.5F * std::min(x, y);
    mRect = D2D1::RectF(x - sideHalf, y - sideHalf, x + sideHalf, y + sideHalf);
}

HRESULT MainWindow::createGraphicsResources()
{
    if (mRenderTarget != nullptr)
    {
        return S_OK;
    }

    RECT clientRect{};
    GetClientRect(mHwnd, &clientRect);
    const D2D1_SIZE_U size = D2D1::SizeU(clientRect.right, clientRect.bottom);
    const D2D1_COLOR_F brushColor = D2D1::ColorF(D2D1::ColorF::Blue);
    HRESULT hr{};
    if (SUCCEEDED(hr = mFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(mHwnd, size),
        &mRenderTarget))
        && SUCCEEDED(hr = mRenderTarget->CreateSolidColorBrush(brushColor, &mBrush)))
    {
        calculateLayout();
    }
    return hr;
}

void MainWindow::discardGraphicsResources()
{
    util::SafeRelease(&mRenderTarget);
    util::SafeRelease(&mBrush);
}

void MainWindow::onPaint()
{
    if (FAILED(createGraphicsResources()))
    {
        return;
    }

    PAINTSTRUCT ps{};
    BeginPaint(mHwnd, &ps);
    mRenderTarget->BeginDraw();
    mRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
    mRenderTarget->FillRectangle(mRect, mBrush);
    HRESULT hr = mRenderTarget->EndDraw();
    if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
    {
        discardGraphicsResources();
    }
    EndPaint(mHwnd, &ps);
}

void MainWindow::resize()
{
    if (mRenderTarget == nullptr)
    {
        return;
    }

    RECT rect{};
    GetClientRect(mHwnd, &rect);
    const D2D1_SIZE_U size = D2D1::SizeU(rect.right, rect.bottom);
    mRenderTarget->Resize(size);
    calculateLayout();
    InvalidateRect(mHwnd, nullptr, FALSE);
}
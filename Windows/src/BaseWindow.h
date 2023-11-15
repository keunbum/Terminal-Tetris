#pragma once

#include <windows.h>

template <class DERIVED_CLASS>
class BaseWindow
{
public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        DERIVED_CLASS* pDerived = nullptr;
        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            pDerived = (DERIVED_CLASS*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pDerived);
            pDerived->mHwnd = hwnd;
        }
        else
        {
            pDerived = (DERIVED_CLASS*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }

        if (pDerived != nullptr)
        {
            return pDerived->handleMessage(uMsg, wParam, lParam);
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    BaseWindow() : mHwnd(nullptr) {}

    BOOL CreateHwnd(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    )
    {
        WNDCLASS wc{};
        wc.lpfnWndProc = DERIVED_CLASS::WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = getClassName();
        RegisterClass(&wc);

        mHwnd = CreateWindowEx(
            dwExStyle, getClassName(), lpWindowName, dwStyle, x, y,
            nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(nullptr), (LPVOID)this
        );

        return BOOL(mHwnd != nullptr);
    }

    HWND GetHwnd() const { return mHwnd; }

protected:
    virtual PCWSTR  getClassName() const = 0;
    virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND mHwnd;
};
#pragma once

template <class DERIVED_TYPE>
class BaseWindow
{
public:
  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    DERIVED_TYPE* pThis = nullptr;
    if (uMsg == WM_NCCREATE)
    {
      CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
      pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

      pThis->m_hwnd = hwnd;
    }
    else
    {
      pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (pThis != nullptr)
    {
      return pThis->HandleMessage(uMsg, wParam, lParam);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }

  BaseWindow() : m_hwnd(nullptr) {}

  BOOL Create(
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
    wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = ClassName();
    RegisterClass(&wc);

    m_hwnd = CreateWindowEx(
      dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
      nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(nullptr), (LPVOID)this
    );

    return BOOL(m_hwnd != nullptr);
  }

  HWND Window() const { return m_hwnd; }

protected:
  virtual PCWSTR  ClassName() const = 0;
  virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

  HWND m_hwnd;
};
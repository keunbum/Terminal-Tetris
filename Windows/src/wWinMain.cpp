#include "MainWindow.h"

int RunMainWindow(int nShowCmd)
{
    MainWindow win;
    if (!win.CreateHwnd(L"Circle Sample", WS_OVERLAPPEDWINDOW))
    {
        return EXIT_SUCCESS;
    }
    ShowWindow(win.GetHwnd(), nShowCmd);

    BOOL result;
    MSG msg{};
    /* Run the message loop. */
    while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    if (result == -1)
    {
        /* Handle some errors. */
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int WINAPI wWinMain(
    _In_ HINSTANCE,
    _In_opt_ HINSTANCE,
    _In_ LPWSTR,
    _In_ int nShowCmd)
{
    return RunMainWindow(nShowCmd);
}
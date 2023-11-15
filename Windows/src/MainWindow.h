#pragma once

#include <d2d1.h>
#include <windows.h>

#pragma comment(lib, "d2d1")

#include "BaseWindow.h"
#include "util.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
    MainWindow();
    PCWSTR  getClassName() const override { return L"TETRIS Window Class"; }
    LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
private:
    void    calculateLayout();
    HRESULT createGraphicsResources();
    void    discardGraphicsResources();
    void    onPaint();
    void    resize();

    ID2D1Factory* mFactory;
    ID2D1HwndRenderTarget* mRenderTarget;
    ID2D1SolidColorBrush* mBrush;
    D2D1_RECT_F mRect;
};

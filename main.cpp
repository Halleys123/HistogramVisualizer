#include <Windows.h>
#include "WndProc.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSA mainWc = {0};
    mainWc.hInstance = hInstance;
    mainWc.lpfnWndProc = MainWndProc;
    mainWc.lpszClassName = "MainWindowClass";
    mainWc.hCursor = LoadCursor(NULL, IDC_ARROW);
    mainWc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassA(&mainWc);

    WNDCLASSA imgWc = {0};
    imgWc.hInstance = hInstance;
    imgWc.lpfnWndProc = ImgWndProc;
    imgWc.lpszClassName = "ImageWindowClass";
    imgWc.hCursor = LoadCursor(NULL, IDC_ARROW);
    imgWc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassA(&imgWc);

    WNDCLASSA histWc = {0};
    histWc.hInstance = hInstance;
    histWc.lpfnWndProc = HistWndProc;
    histWc.lpszClassName = "HistogramWindowClass";
    histWc.hCursor = LoadCursor(NULL, IDC_ARROW);
    histWc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassA(&histWc);

    HWND mainWindow = CreateWindowA("MainWindowClass", "Image Loader", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                    CW_USEDEFAULT, CW_USEDEFAULT, 500, 100, NULL, NULL, hInstance, NULL);

    if (!mainWindow)
        return 1;

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
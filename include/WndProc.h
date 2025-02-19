#pragma once
#include <Windows.h>

#define IDC_EDIT 1001
#define IDC_BUTTON 1002

struct ChildWindowParams
{
    unsigned char *imgData;
    int width;
    int height;
    int channels;
};

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ImgWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK HistWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
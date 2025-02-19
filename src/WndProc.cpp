#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "WndProc.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <Windows.h>

#define FRAME_RATE 60

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit, hButton;

    switch (msg)
    {
    case WM_CREATE:
    {
        hEdit = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                              10, 10, 300, 25, hwnd, (HMENU)IDC_EDIT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        hButton = CreateWindowA("BUTTON", "Load Image", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                320, 10, 100, 25, hwnd, (HMENU)IDC_BUTTON, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        break;
    }
    case WM_COMMAND:
    {
        if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_BUTTON)
        {
            char path[MAX_PATH];
            GetWindowTextA(hEdit, path, MAX_PATH);

            int width, height, channels;
            unsigned char *imgData = stbi_load(path, &width, &height, &channels, 0);
            if (!imgData)
            {
                MessageBoxA(hwnd, "Failed to load image", "Error", MB_OK);
                break;
            }

            size_t imgSize = width * height * channels;

            // Prepare parameters for image window
            unsigned char *imgCopy1 = (unsigned char *)malloc(imgSize);
            memcpy(imgCopy1, imgData, imgSize);
            ChildWindowParams *params1 = new ChildWindowParams{imgCopy1, width, height, channels};

            // Prepare parameters for histogram window
            unsigned char *imgCopy2 = (unsigned char *)malloc(imgSize);
            memcpy(imgCopy2, imgData, imgSize);
            ChildWindowParams *params2 = new ChildWindowParams{imgCopy2, width, height, channels};

            stbi_image_free(imgData);

            // Create image window
            CreateWindowA("ImageWindowClass", "Image Viewer", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                          CW_USEDEFAULT, CW_USEDEFAULT, width, height, hwnd, NULL, NULL, params1);

            // Create histogram window
            CreateWindowA("HistogramWindowClass", "Histogram", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                          CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, hwnd, NULL, NULL, params2);
        }
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ImgWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static ChildWindowParams *params = nullptr;

    switch (msg)
    {
    case WM_CREATE:
    {
        params = (ChildWindowParams *)((LPCREATESTRUCT)lParam)->lpCreateParams;
        break;
    }
    case WM_SIZE:
    {
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);

        if (params && params->imgData)
        {
            BITMAPINFO bmi = {0};
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = params->width;
            bmi.bmiHeader.biHeight = -params->height;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = params->channels * 8;
            bmi.bmiHeader.biCompression = BI_RGB;

            StretchDIBits(hdc, 0, 0, clientRect.right, clientRect.bottom,
                          0, 0, params->width, params->height, params->imgData, &bmi, DIB_RGB_COLORS, SRCCOPY);
        }

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        if (params)
        {
            free(params->imgData);
            delete params;
        }
        break;
    }
    default:
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK HistWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct HistogramData
    {
        ChildWindowParams *params;
        int intensityCount[256] = {0};
    };

    static HistogramData *histData = nullptr;

    switch (msg)
    {
    case WM_CREATE:
    {
        ChildWindowParams *params = (ChildWindowParams *)((LPCREATESTRUCT)lParam)->lpCreateParams;
        histData = new HistogramData{params};

        for (int i = 0; i < params->width * params->height * params->channels; i++)
            histData->intensityCount[params->imgData[i]]++;

        SetTimer(hwnd, 1, 1000 / FRAME_RATE, NULL);
        break;
    }
    case WM_TIMER:
    {
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        int clientWidth = clientRect.right - clientRect.left;
        int clientHeight = clientRect.bottom - clientRect.top;

        if (histData)
        {
            int maxCount = 0;
            for (int i = 0; i < 256; i++)
                if (histData->intensityCount[i] > maxCount)
                    maxCount = histData->intensityCount[i];

            int barWidth = clientWidth / 256;
            for (int i = 0; i < 256; i++)
            {
                int barHeight = (histData->intensityCount[i] * clientHeight) / maxCount;
                RECT barRect = {i * barWidth, clientHeight - barHeight, (i + 1) * barWidth, clientHeight};
                HBRUSH brush = CreateSolidBrush(RGB(i, i, i));
                FillRect(hdc, &barRect, brush);
                DeleteObject(brush);
            }
        }

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        KillTimer(hwnd, 1);
        if (histData)
        {
            free(histData->params->imgData);
            delete histData->params;
            delete histData;
        }
        break;
    }
    default:
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
    return 0;
}
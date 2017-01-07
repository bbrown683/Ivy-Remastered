#include "Window.h"

bool Window::PollWindowEvents()
{
    MSG msg;
    while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

void Window::Close()
{
    RemoveProp(hWnd, TEXT("WINDOW"));
    UnregisterWindowClass();
    DestroyWindow(hWnd);
    open = false;
}

HDC Window::GetPlatformDisplay()
{
    return hDC;
}

HWND Window::GetPlatformWindow()
{
    return hWnd;
}

bool Window::Create()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    if (RegisterWindowClass(hInstance))
    {
        DWORD dwStyle = WS_OVERLAPPEDWINDOW;

        HWND hWnd = CreateWindowA(TEXT("IVY_APP"), title.c_str(), dwStyle,
            x, y, width, height, nullptr, nullptr, hInstance, nullptr);

        if (!hWnd)
            return false;

        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);

        this->hDC = GetDC(hWnd);
        this->hWnd = hWnd;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->title = title;

        // This will allow us to store the reference inside the Window Procedure.
        SetProp(hWnd, TEXT("WINDOW"), this);

        return open = true;
    }

    return false;
}

bool Window::RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = WindowProcedure;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = reinterpret_cast<HBRUSH>(NULL_BRUSH);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = TEXT("IVY_APP");
    wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
        return false;

    return true;
}

void Window::UnregisterWindowClass()
{
    UnregisterClass(TEXT("IVY_APP"), GetModuleHandle(nullptr));
}

LRESULT Window::WindowEventHandler(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        Close();
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT Window::WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Retieve a pointer to the window.
    Window* window = reinterpret_cast<Window*>(GetProp(hWnd, TEXT("WINDOW")));

    // Pointer will be null until window is "fully constructed."
    if (!window)
        return DefWindowProc(hWnd, msg, wParam, lParam);

    // Once the pointer exists we can call our own event handler for the object.
    return window->WindowEventHandler(msg, wParam, lParam);
}
#ifndef IVY_WINDOW_H
#define IVY_WINDOW_H

#include <Windows.h>
#include <string>
#include <queue>

class Window
{
    HDC hDC;
    HWND hWnd;

    unsigned int width;
    unsigned int height;
    int x;
    int y;
    std::string title;
    bool fullscreen;

public:

    bool open = false;

    bool PollWindowEvents();
    void Close();
    HDC GetPlatformDisplay();
    HWND GetPlatformWindow();
    bool Create();

    Window(unsigned int width, unsigned int height, int x, int y,
        std::string title, bool fullscreen)
    {
        this->width = width;
        this->height = height;
        this->x = x;
        this->y = y;
        this->title = title;
        this->fullscreen = fullscreen;
    }

    ~Window()
    {
        if (open)
            Window::Close();
    }

    bool RegisterWindowClass(HINSTANCE hInstance);
    void UnregisterWindowClass();
    LRESULT WindowEventHandler(UINT msg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif // IVY_WINDOW_H
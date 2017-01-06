#include "Renderer.h"
#include "Window.h"

int main()
{
    Window window(1080, 720, 100, 100, "Ivy", false);
    if (window.Create())
    {
        Renderer renderer(2, 0, 8, 8, 8, 8, 24, 8, false, 0, false);
        renderer.Create(window.GetPlatformWindow(), window.GetPlatformDisplay());

        while (window.open)
        {
            renderer.Clear(Color::CornflowerBlue);

            renderer.Present();
            window.PollWindowEvents();
        }
    }

    return 0;
}
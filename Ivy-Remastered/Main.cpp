#include "ivyRenderer.h"
#include "Window.h"

int main()
{
    Window window(1080, 720, 10, 10, "test", false);
    if (window.Create())
    {
        ivyRenderer renderer(2, 0, 8, 8, 8, 8, 24, 8, false, 0, false);
        renderer.Create(window.GetPlatformWindow(), window.GetPlatformDisplay());

        while (window.open)
        {
            renderer.Clear(ivyColor::CornflowerBlue);

            renderer.Present();
            window.PollWindowEvents();
        }
    }

    return 0;
}
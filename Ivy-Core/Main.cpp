#include "Window.h"
#include "Graphics/Camera.h"
#include "Graphics/Model.h"

using namespace Ivy::Graphics;

int main(int argc, char** argv)
{
    Window window(1080, 720, 100, 100, "Ivy", false);
    if (window.Create())
    {
        Renderer renderer(8, 8, 8, 8, 24, 8, 0, false, true, false);
        renderer.Create(window.GetPlatformWindow(), window.GetPlatformDisplay());

        // Fill out our shader data.
        Program program("vert.txt", "frag.txt");
        program.Create();

        Camera camera(program, glm::vec3(15.0f, 5.0f, -20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        camera.Create();

        Model model(program);
        model.Load("cube.ply");

        while (window.open)
        {
            renderer.Clear(Color::CornflowerBlue);
            
            model.Draw();
            
            renderer.SwapBuffers();
            window.PollWindowEvents();
        }
    }

    return 0;
}
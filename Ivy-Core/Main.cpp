#include "Window.h"
#include "Graphics/Camera.h"
#include "Graphics/Model.h"
#include "Graphics/Colors.h"

using namespace Ivy::Graphics;

int main(int argc, char** argv)
{
    Window window(1080, 720, 100, 100, "Ivy", false);
    if (window.Create())
    {
        Renderer renderer(8, 8, 8, 8, 24, 8, 0, false, true, false);
        renderer.Create(window.GetPlatformWindow(), window.GetPlatformDisplay());

        Program program("vert.txt", "frag.txt");
        program.Create();

        Camera camera(&program, glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), 
            glm::radians(45.0f), 1080, 720);
        camera.Create();

        Model model(&program);
        model.Load("monocube.dae");

        Model model2(&program);
        model2.Load("monocube.dae");
        model2.SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));

        Model model3(&program);
        model3.Load("monocube.dae");
        model3.SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));

        Model model4(&program);
        model4.Load("monocube.dae");
        model4.SetPosition(glm::vec3(-5.0f, 0.0f, 0.0f));

        while (window.open)
        {
            renderer.Clear(Colors::CornflowerBlue);
            
            model.Draw();
            model2.Draw();
            model3.Draw();
            model4.Draw();

            model.SetRotation(glm::vec3(0.0f, 0.000005f, 0.0f));

            renderer.SwapBuffers();
            window.PollWindowEvents();
        }
    }

    return 0;
}
#include "Renderer.h"
#include "Program.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Window.h"

int main()
{
    Window window(1080, 720, 100, 100, "Ivy", false);
    if (window.Create())
    {
        Renderer renderer(8, 8, 8, 8, 24, 8, 0, false, true);
        renderer.Create(window.GetPlatformWindow(), window.GetPlatformDisplay());

        // Fill out our shader data.
        Program program("vert.txt", "frag.txt");
        program.Create();

        std::vector<Vertex> vertices;
        Vertex vertex0;
        glm::vec3 vertposition0 = { 0.0f,  0.5f, 0.0f };
        glm::vec4 vertcolor0 = { 1.0f, 0.0f, 0.0f, 1.0f };
        vertex0.m_Position = vertposition0;
        vertex0.m_Color0 = vertcolor0;

        Vertex vertex1;
        glm::vec3 vertposition1 = { -0.5f, -0.5f, 0.0f };
        glm::vec4 vertcolor1 = { 0.0f, 1.0f, 0.0f, 1.0f };
        vertex1.m_Position = vertposition1;
        vertex1.m_Color0 = vertcolor1;

        Vertex vertex2;
        glm::vec3 vertposition2 = { 0.5f, -0.5f, 0.0f };
        glm::vec4 vertcolor2 = { 0.0f, 0.0f, 1.0f, 1.0f };
        vertex2.m_Position = vertposition2;
        vertex2.m_Color0 = vertcolor2;

        vertices.push_back(vertex0);
        vertices.push_back(vertex1);
        vertices.push_back(vertex2);

        VertexBuffer vBuffer;
        vBuffer.SetVertices(vertices);
        vBuffer.Create();

        vBuffer.Bind();

        std::vector<GLushort> indices = { 0, 1, 2 };
        ElementBuffer eBuffer;
        eBuffer.SetIndices(indices);
        eBuffer.Bind();

        while (window.open)
        {
            renderer.Clear(Color::CornflowerBlue);

            program.MakeActive();
            eBuffer.Draw();
            program.MakeInactive();

            renderer.SwapBuffers();
            window.PollWindowEvents();
        }

        eBuffer.Unbind();
        vBuffer.Bind();
    }

    return 0;
}
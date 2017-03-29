#include "Window.h"
#include <iostream>

bool Ivy::Window::Create() {
  if (!glfwInit())
    return false;

  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfw_window_ = glfwCreateWindow(1080, 720, "Test", nullptr, nullptr);
  if (!glfw_window_) {
      glfwTerminate();
      return false;
  }

  glfwSetWindowUserPointer(glfw_window_, this);
  glfwSetWindowSizeCallback(glfw_window_, reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window_))->OnResize);
  glfwMakeContextCurrent(glfw_window_);
  return true;
}

void Ivy::Window::OnResize(GLFWwindow* window, int width, int height) {
    std::cout << width << "x" << height << std::endl;
}

void Ivy::Window::PollEvents() {
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glfw_window_))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(glfw_window_);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

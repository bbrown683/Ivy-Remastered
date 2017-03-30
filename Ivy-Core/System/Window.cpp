// MIT License
//
// Copyright (c) 2017 Ben Brown
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Window.h"

Ivy::System::Window::~Window() {
  glfwTerminate();
}

Ivy::System::Window::Window(int width, int height, std::string title) : 
  width_(width), height_(height), title_(title) {
  if (!glfwInit())
    throw std::exception("Failed to initialize GLFW!");

  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  glfw_window_ptr_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
  if (!glfw_window_ptr_) {
    glfwTerminate();
    throw std::exception("Failed to initialize GLFW window!");
  }

  glfwSetWindowUserPointer(glfw_window_ptr_, this);
  
  // Register callbacks.
  glfwSetCursorPosCallback(glfw_window_ptr_, CursorPosCallback);
  glfwSetKeyCallback(glfw_window_ptr_, KeyActionCallback);
  glfwSetMouseButtonCallback(glfw_window_ptr_, MouseActionCallback);
  glfwSetWindowRefreshCallback(glfw_window_ptr_, RefreshCallback);
  glfwSetWindowSizeCallback(glfw_window_ptr_, ResizeCallback);
}

void Ivy::System::Window::Run() {
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(glfw_window_ptr_))
  {
    /* Force update event. */
    OnRefresh(glfw_window_ptr_);

    /* Swap front and back buffers */
    glfwSwapBuffers(glfw_window_ptr_);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
}

void Ivy::System::Window::Run(int update_rate) {
}

void Ivy::System::Window::MakeCurrent() {
  glfwMakeContextCurrent(glfw_window_ptr_);
}

void Ivy::System::Window::Close() {
}

void Ivy::System::Window::set_x_pos(double x_pos) {
  glfwSetWindowPos(glfw_window_ptr_, static_cast<int>(x_pos), static_cast<int>(y_pos_));
  x_pos_ = x_pos;
}

void Ivy::System::Window::set_y_pos(double y_pos) {
  glfwSetWindowPos(glfw_window_ptr_, static_cast<int>(x_pos_), static_cast<int>(y_pos));
  y_pos_ = y_pos;
}

void Ivy::System::Window::set_width(int width) {
  glfwSetWindowSize(glfw_window_ptr_, width, height_);
  width_ = width;
}

void Ivy::System::Window::set_height(int height) {
  glfwSetWindowSize(glfw_window_ptr_, width_, height);
  height_ = height;
}

void Ivy::System::Window::set_title(std::string title) {
  glfwSetWindowTitle(glfw_window_ptr_, title.c_str());
  title_ = title;
}

void Ivy::System::Window::OnClose(GLFWwindow* glfw_window_ptr) {
}

void Ivy::System::Window::OnCursorMove(GLFWwindow* glfw_window_ptr, double x_pos, double y_pos) {
}

void Ivy::System::Window::OnFocus(GLFWwindow* glfw_window_ptr, int focused) {
}

void Ivy::System::Window::OnIconify(GLFWwindow* glfw_window_ptr, int iconified) {
}

void Ivy::System::Window::OnKeyAction(GLFWwindow* glfw_window_ptr, int key, int scancode, int action, int mods) {
}

void Ivy::System::Window::OnMouseAction(GLFWwindow * glfw_window_ptr, int button, int action, int mods) {
}

void Ivy::System::Window::OnRefresh(GLFWwindow* glfw_window_ptr) {

}

void Ivy::System::Window::OnResize(GLFWwindow* glfw_window_ptr, int width, int height) {
  
}

void Ivy::System::Window::CloseCallback(GLFWwindow* glfw_window_ptr) {
  static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr))->OnClose(glfw_window_ptr);
}

void Ivy::System::Window::CursorPosCallback(GLFWwindow* glfw_window_ptr, double x_pos, double y_pos) {
  static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr))->OnCursorMove(glfw_window_ptr, x_pos, y_pos);
}

void Ivy::System::Window::FocusCallback(GLFWwindow* glfw_window_ptr, int focused) {
  static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr))->OnFocus(glfw_window_ptr, focused);
}

void Ivy::System::Window::IconifyCallback(GLFWwindow* glfw_window_ptr, int iconified) {
    static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr))->OnIconify(glfw_window_ptr, iconified);
}

void Ivy::System::Window::KeyActionCallback(GLFWwindow* glfw_window_ptr, int key, int scancode, int action, int mods) {
  static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr))->OnKeyAction(glfw_window_ptr, key, scancode, action, mods);
}

void Ivy::System::Window::MouseActionCallback(GLFWwindow * glfw_window_ptr, int button, int action, int mods) {
  static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr))->OnMouseAction(glfw_window_ptr, button, action, mods);
}

void Ivy::System::Window::RefreshCallback(GLFWwindow* glfw_window_ptr) {
  static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr))->OnRefresh(glfw_window_ptr);
}

void Ivy::System::Window::ResizeCallback(GLFWwindow* glfw_window_ptr, int width, int height) {
  static_cast<Window*>(glfwGetWindowUserPointer(glfw_window_ptr))->OnResize(glfw_window_ptr, width, height);
}

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

#ifndef __GAMEWINDOW_H__
#define __GAMEWINDOW_H__
#include "Window.h"

#include <iostream>

namespace Ivy {
namespace System {
class GameWindow : public Window {
 public:
  GameWindow(int width, int height, std::string title) : Window(width, height, title)
  {
  }

 private:
  // Inherited via Window
  virtual void OnClose(GLFWwindow* glfw_window_ptr) override;
  virtual void OnCursorMove(GLFWwindow* glfw_window_ptr, double x_pos, double y_pos) override;
  virtual void OnFocus(GLFWwindow* glfw_window_ptr, int focused) override;
  virtual void OnIconify(GLFWwindow*  glfw_window_ptr, int iconified) override;
  virtual void OnKeyAction(GLFWwindow* glfw_window_ptr, int key, int scancode, int action, int mods) override;
  virtual void OnRefresh(GLFWwindow* glfw_window_ptr) override;
  virtual void OnResize(GLFWwindow* glfw_window_ptr, int width, int height) override;
};
}
}

#endif
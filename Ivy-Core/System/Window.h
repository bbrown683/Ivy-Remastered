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

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>
#include <vector>

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>

namespace Ivy {
namespace System {
/// @brief Abstract class for creating a window with an OpenGL ES 2.0 Context.
///
///
class Window {
 public:
  /// @brief
  /// 
  ///
  Window(int width, int height, std::string title);
  virtual ~Window();

  /// @brief
  ///
  ///
  ///
  void Run();

  /// @brief
  ///
  ///
  ///
  void Run(int update_rate);
  
  /// @brief
  ///
  ///
  ///
  void MakeCurrent();
  
  /// @brief
  ///
  ///
  ///
  void Close();

  /// @brief
  ///
  ///
  ///
  bool is_open() { return open_; }

  /// @brief
  ///
  ///
  ///
  double get_x_pos() { return x_pos_; }
  
  /// @brief
  ///
  ///
  ///
  void set_x_pos(double x_pos);
  
  /// @brief
  ///
  ///
  ///
  double get_y_pos() { return y_pos_; }
  
  /// @brief
  ///
  ///
  ///
  void set_y_pos(double y_pos);
  
  /// @brief
  ///
  ///
  ///
  int get_width() { return width_; }
  
  /// @brief
  ///
  ///
  ///
  void set_width(int width);
  
  /// @brief
  ///
  ///
  ///
  int get_height() { return height_; }
  
  /// @brief
  ///
  ///
  ///
  void set_height(int height);
  
  /// @brief
  ///
  ///
  ///
  std::string get_title() { return title_; }
  
  /// @brief
  ///
  ///
  ///
  void set_title(std::string title);
  
  /// @brief
  ///
  ///
  ///
  GLFWwindow* get_glfw_window_ptr() { return glfw_window_ptr_; }

 protected:

  /// @brief
  ///
  ///
  ///
  virtual void OnClose(GLFWwindow* glfw_window_ptr);
  
  /// @brief
  ///
  ///
  ///
  virtual void OnCursorMove(GLFWwindow* glfw_window_ptr, double x_pos, double y_pos);
  
  /// @brief
  ///
  ///
  ///
  virtual void OnFocus(GLFWwindow* glfw_window_ptr, int focused);
  
  /// @brief
  ///
  ///
  ///
  virtual void OnIconify(GLFWwindow* glfw_window_ptr, int iconified);
  
  /// @brief
  ///
  ///
  ///
  virtual void OnKeyAction(GLFWwindow* glfw_window_ptr, int key, int scancode, int action, int mods);
  
  /// @brief
  ///
  ///
  ///
  virtual void OnMouseAction(GLFWwindow* glfw_window_ptr, int button, int action, int mods);
  
  /// @brief A Refresh event is triggered when the framebuffer needs to be redrawn. 
  ///
  ///
  ///
  virtual void OnRefresh(GLFWwindow* glfw_window_ptr);
  
  /// @brief
  ///
  ///
  ///
  virtual void OnResize(GLFWwindow* glfw_window_ptr, int width, int height);

 private:
  
  /// @brief
  ///
  ///
  ///
  static void CloseCallback(GLFWwindow* glfw_window_ptr);
  
  /// @brief
  ///
  ///
  ///
  static void CursorPosCallback(GLFWwindow* glfw_window_ptr, double x_pos, double y_pos);
  
  /// @brief
  ///
  ///
  ///
  static void FocusCallback(GLFWwindow* glfw_window_ptr, int focused);
  
  /// @brief
  ///
  ///
  ///
  static void IconifyCallback(GLFWwindow* glfw_window_ptr, int iconified);
  
  /// @brief
  ///
  ///
  ///
  static void KeyActionCallback(GLFWwindow* glfw_window_ptr, int key, int scancode, int action, int mods);
  
  /// @brief
  ///
  ///
  ///
  static void MouseActionCallback(GLFWwindow* glfw_window_ptr, int button, int action, int mods);
  
  /// @brief
  ///
  ///
  ///
  static void RefreshCallback(GLFWwindow* glfw_window_ptr);
  
  /// @brief
  ///
  ///
  ///
  static void ResizeCallback(GLFWwindow* glfw_window_ptr, int width, int height);

  bool open_;
  double x_pos_;
  double y_pos_;
  int width_;
  int height_;
  std::string title_;
  GLFWwindow* glfw_window_ptr_;
};
}
}

#endif
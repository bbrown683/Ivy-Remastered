#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <functional>
#include <GLFW/glfw3.h>

namespace Ivy {
class Window {
 public:
  Window(int width, int height) 
    : width_(width), 
      height_(height) 
    {
    }

  bool Create();
  void OnResize(GLFWwindow* window, int width, int height);
  void PollEvents();

 private:
  std::function<void(GLFWwindowsizefun)> resize_callback_;

  int width_;
  int height_;
  int x_;
  int y_;
  GLFWwindow* glfw_window_;
};
}

#endif
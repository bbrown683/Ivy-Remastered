#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif 

#ifndef EGL_EGLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES 1
#endif

#include <export.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>

#include "GameWindow.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Objects/Model/Model.h"
#include "../Graphics/Colors.h"

#include <iostream>

void Ivy::System::GameWindow::OnResize(GLFWwindow* glfw_window_ptr, int width, int height) {
    std::cout << width << "x" << height << std::endl;
}

void Ivy::System::GameWindow::OnCursorMove(GLFWwindow* glfw_window_ptr, double x_pos, double y_pos) {

}

void Ivy::System::GameWindow::OnKeyAction(GLFWwindow* glfw_window_ptr, int key, int scancode, int action, int mods) {
    
}

void Ivy::System::GameWindow::OnClose(GLFWwindow* glfw_window_ptr) {
}

void Ivy::System::GameWindow::OnFocus(GLFWwindow* glfw_window_ptr, int focused) {
}

void Ivy::System::GameWindow::OnIconify(GLFWwindow* glfw_window_ptr, int iconified) {

}

void Ivy::System::GameWindow::OnRefresh(GLFWwindow* glfw_window_ptr) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}

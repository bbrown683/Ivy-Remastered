/*
MIT License

Copyright (c) 2017 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <assert.h>
#include <vector>
#include <iostream>
#include <memory>

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif 

#ifndef EGL_EGLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES 1
#endif

#include <glm/glm.hpp>

#include <export.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>

#include "../Symbols.h"

namespace Ivy {
namespace Graphics {
class IVY_API Renderer {
 public:
  Renderer(EGLint red_bits, EGLint green_bits, EGLint blue_bits, EGLint alpha_bits,
  EGLint depth_bits, EGLint stencil_bits, EGLint swap_interval, EGLint samples,
  bool debug, bool no_error)
    : red_bits_(red_bits),
      green_bits_(green_bits),
      blue_bits_(blue_bits),
      alpha_bits_(alpha_bits),
      depth_bits_(depth_bits),
      stencil_bits_(stencil_bits),
      swap_interval_(swap_interval),
      samples_(samples),
      debug_(debug),
      no_error_(no_error) 
    {
    }
     
  ~Renderer();
  
  /// @brief Adjusts the render viewport, useful in the event of window resizes.
  /// @param width width of the viewport.
  /// @param height height of the viewport.
  void AdjustViewport(GLuint width, GLuint height);
  
  /// @brief clears the backbuffer to the specified 3-component vector color.
  /// @param color the 3-component vector color.
  void Clear(glm::vec3 color);
  
  /// @brief creates the rendering context for the specified window and display.
  /// @param native_window the window handle for the specific operating system.
  /// @param native_display the display handle for the specific operating system.
  /// @return a boolean on the success of context creation.
  bool Create(EGLNativeWindowType native_window, EGLNativeDisplayType native_display);

  /// @brief forcefully cleans up the renderer instance before destructor call.
  void Destroy(void);
  void Draw(void);
  bool IsInitialized(void);
  void SetCullMode(GLenum cull_mode);
  void SetFrontFace(GLenum front_face);
  void EnableCapability(GLenum capability);
  void SwapBuffers(void);

  EGLint get_red_bits(void) { return red_bits_; }
  void set_red_bits(EGLint bits) { red_bits_ = bits; }
  EGLint get_green_bits(void) { return green_bits_; }
  void set_green_bits(EGLint bits) { green_bits_ = bits; }
  EGLint get_blue_bits(void) { return blue_bits_; }
  void set_blue_bits(EGLint bits) { blue_bits_ = bits; }
  EGLint get_alpha_bits(void) { return alpha_bits_; }
  void set_alpha_bits(EGLint bits) { alpha_bits_ = bits; }
  EGLint get_depth_bits(void) { return depth_bits_; }
  void set_depth_bits(EGLint bits) { depth_bits_ = bits; }
  EGLint get_stencil_bits(void) { return stencil_bits_; }
  void set_stencil_bits(EGLint bits) { stencil_bits_ = bits; }
  EGLint get_swap_interval(void) { return swap_interval_; }
  void set_swap_interval(EGLint interval);
  EGLint get_back_buffer_width(void) { return back_buffer_width_; }
  void set_back_buffer_width(EGLint width) { back_buffer_width_ = width; }
  EGLint get_back_buffer_height(void) { return back_buffer_height_; }
  void set_back_buffer_height(EGLint height) { back_buffer_width_ = height; };
 private:
  EGLint red_bits_;
  EGLint green_bits_;
  EGLint blue_bits_;
  EGLint alpha_bits_;
  EGLint depth_bits_;
  EGLint stencil_bits_;
  EGLint swap_interval_;
  EGLint samples_;
  bool debug_;
  bool no_error_;

  GLint back_buffer_width_;
  GLint back_buffer_height_;

  EGLDisplay display_;
  EGLConfig config_;
  EGLSurface surface_;
  EGLContext context_;
};
}
}

#endif // IVY_RENDERER_H
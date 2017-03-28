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

#include "Renderer.h"

Ivy::Graphics::Renderer::~Renderer(void) {
    Renderer::Destroy();
}

void Ivy::Graphics::Renderer::AdjustViewport(GLuint width, GLuint height) {
    // On the event of a window resize we need to also fix the viewport.
    glViewport(0, 0, width, height);
}

void Ivy::Graphics::Renderer::Clear(glm::vec3 color) {
    // Clear each buffer and set the back buffer to a specific color.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, 1.0f);
}

bool Ivy::Graphics::Renderer::Create(EGLNativeWindowType native_window, EGLNativeDisplayType native_display) {
    display_ = eglGetDisplay(native_display);
    GLint version_major, version_minor;
    if (!eglInitialize(display_, &version_major, &version_minor))
        return false;

    // Set our bits for each pixel.
    const EGLint configAttributes[] = {
        EGL_RED_SIZE,       (red_bits_ >= 0) ? red_bits_ : EGL_DONT_CARE,
        EGL_GREEN_SIZE,     (green_bits_ >= 0) ? green_bits_ : EGL_DONT_CARE,
        EGL_BLUE_SIZE,      (blue_bits_ >= 0) ? blue_bits_ : EGL_DONT_CARE,
        EGL_ALPHA_SIZE,     (alpha_bits_ >= 0) ? alpha_bits_ : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     (depth_bits_ >= 0) ? depth_bits_ : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (stencil_bits_ >= 0) ? stencil_bits_ : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (samples_ >= 1) ? GL_TRUE : GL_FALSE,
        EGL_SAMPLES,        samples_,
        EGL_NONE
    };

    // Choosing a config will give us a configuration "closest" to what we passed in,
    // which means it is not guaranteed to be the same. We also only want a single configuration.
    EGLint configCount;
    if (!eglChooseConfig(display_, configAttributes, &config_, 1, &configCount) || (configCount != 1))
        return false;

    // Get the actual bit values for each after choosing the configuration.
    eglGetConfigAttrib(display_, config_, EGL_RED_SIZE, &red_bits_);
    eglGetConfigAttrib(display_, config_, EGL_GREEN_SIZE, &green_bits_);
    eglGetConfigAttrib(display_, config_, EGL_BLUE_SIZE, &blue_bits_);
    eglGetConfigAttrib(display_, config_, EGL_ALPHA_SIZE, &alpha_bits_);
    eglGetConfigAttrib(display_, config_, EGL_DEPTH_SIZE, &depth_bits_);
    eglGetConfigAttrib(display_, config_, EGL_STENCIL_SIZE, &stencil_bits_);

    // Creates the surface for the display with the specified configuration and surface attributes.
    surface_ = eglCreateWindowSurface(display_, config_, native_window, nullptr);
    if (eglGetError() != EGL_SUCCESS)
        return false;

    // Set the GLES context attributes.
    std::vector<EGLint> contextAttributes;
    contextAttributes.push_back(EGL_CONTEXT_MAJOR_VERSION);
    contextAttributes.push_back(2);
    contextAttributes.push_back(EGL_CONTEXT_MINOR_VERSION);
    contextAttributes.push_back(0);
    contextAttributes.push_back(EGL_CONTEXT_OPENGL_DEBUG);
    contextAttributes.push_back(debug_ ? EGL_TRUE : EGL_FALSE);
    contextAttributes.push_back(EGL_CONTEXT_OPENGL_NO_ERROR_KHR);
    contextAttributes.push_back(no_error_ ? EGL_TRUE : EGL_FALSE);
    contextAttributes.push_back(EGL_CONTEXT_WEBGL_COMPATIBILITY_ANGLE);
    contextAttributes.push_back(EGL_TRUE);
    contextAttributes.push_back(EGL_NONE);

    // Create the context with the display, configuration and specified context attributes. 
    context_ = eglCreateContext(display_, config_, EGL_NO_CONTEXT, contextAttributes.data());
    if (eglGetError() != EGL_SUCCESS)
        return false;

    // Lastly activate the context.
    eglMakeCurrent(display_, surface_, surface_, context_);
    if (eglGetError() != EGL_SUCCESS)
        return false;

    return true;
}

void Ivy::Graphics::Renderer::Destroy(void) {
    if (surface_ != EGL_NO_SURFACE) {
        assert(display_ != EGL_NO_DISPLAY);
        eglDestroySurface(display_, surface_);
        surface_ = EGL_NO_SURFACE;
    }
    if (context_ != EGL_NO_CONTEXT) {
        assert(display_ != EGL_NO_DISPLAY);
        eglDestroyContext(display_, context_);
        context_ = EGL_NO_CONTEXT;
    }
    if (display_ != EGL_NO_DISPLAY) {
        eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglTerminate(display_);
        display_ = EGL_NO_DISPLAY;
    }
}

bool Ivy::Graphics::Renderer::IsInitialized(void) {
    // Determines if the renderer is initialized.
    return surface_ != EGL_NO_SURFACE &&
        context_ != EGL_NO_CONTEXT &&
        display_ != EGL_NO_DISPLAY;
}

void Ivy::Graphics::Renderer::SetCullMode(GLenum cullMode) {
    glCullFace(cullMode);
}

void Ivy::Graphics::Renderer::SetFrontFace(GLenum frontFace) {
    glFrontFace(frontFace);
}

void Ivy::Graphics::Renderer::EnableCapability(GLenum capability) {
    glEnable(capability);
}

void Ivy::Graphics::Renderer::SwapBuffers(void) {
    // Swaps the front and back buffer.
    eglSwapBuffers(display_, surface_);
}

void Ivy::Graphics::Renderer::set_swap_interval(EGLint interval) {
    // For more information on swap intervals, read the following:
    // https://www.khronos.org/opengl/wiki/Swap_Interval
    eglSwapInterval(display_, interval);
    swap_interval_ = interval;
}

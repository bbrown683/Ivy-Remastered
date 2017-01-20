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

Ivy::Graphics::Renderer::Renderer(EGLint redBits, EGLint greenBits, EGLint blueBits, EGLint alphaBits, EGLint depthBits, EGLint stencilBits,
    EGLint swapInterval, bool enableMultisampling, bool enableDebug, bool disableErrors) {
    this->m_RedBits = redBits;
    this->m_GreenBits = greenBits;
    this->m_BlueBits = blueBits;
    this->m_AlphaBits = alphaBits;
    this->m_DepthBits = depthBits;
    this->m_StencilBits = stencilBits;
    this->m_SwapInterval = swapInterval;
    this->m_MultisamplingEnabled = enableMultisampling;
    this->m_DebugEnabled = enableDebug;
    this->m_DisableErrors = disableErrors;
}

Ivy::Graphics::Renderer::~Renderer(void) {
    Renderer::Destroy();
}

void Ivy::Graphics::Renderer::AdjustViewport(unsigned int width, unsigned int height) {
    // On the event of a window resize we need to also fix the viewport.
    glViewport(0, 0, width, height);
}

void Ivy::Graphics::Renderer::Clear(glm::vec3 color) {
    // Clear each buffer and set the back buffer to a specific color.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, 1.0f);
}

bool Ivy::Graphics::Renderer::Create(EGLNativeWindowType window, EGLNativeDisplayType display) {
    // Function pointer for retrieving the display.
    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = reinterpret_cast
        <PFNEGLGETPLATFORMDISPLAYEXTPROC>(eglGetProcAddress("eglGetPlatformDisplayEXT"));
    if (!eglGetPlatformDisplayEXT) {
        Destroy();
        return false;
    }

    // Set the display attributes, e.g. EGL_DONT_CARE and EGL_PLATFORM_ANGLE_TYPE_DEFAULT_ANGLE
    // Since these are set to the defaults, ANGLE will select the appropriate renderer.
    std::vector<EGLint> displayAttributes;
    displayAttributes.push_back(EGL_PLATFORM_ANGLE_TYPE_ANGLE);
    displayAttributes.push_back(m_Renderer);
    displayAttributes.push_back(EGL_PLATFORM_ANGLE_MAX_VERSION_MAJOR_ANGLE);
    displayAttributes.push_back(m_RendererVersionMajor);
    displayAttributes.push_back(EGL_PLATFORM_ANGLE_MAX_VERSION_MINOR_ANGLE);
    displayAttributes.push_back(m_RendererVersionMinor);

    // Let ANGLE choose the render type: Hardware, Software, WARP
    if (m_RendererType != EGL_DONT_CARE) {
        displayAttributes.push_back(EGL_PLATFORM_ANGLE_DEVICE_TYPE_ANGLE);
        displayAttributes.push_back(m_RendererType);
    }

    if (m_RendererPresentPath != EGL_DONT_CARE) {
        const char *extensionString = static_cast<const char *>(eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS));
        // EGL_ANGLE_experimental_present_path
        // https://github.com/google/angle/blob/master/extensions/EGL_ANGLE_experimental_present_path.txt
        if (!strstr(extensionString, "EGL_ANGLE_experimental_present_path")) {
            Destroy();
            return false;
        }

        displayAttributes.push_back(EGL_EXPERIMENTAL_PRESENT_PATH_ANGLE);
        displayAttributes.push_back(m_RendererPresentPath);
    }
    displayAttributes.push_back(EGL_NONE);

    m_Display = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE,
        reinterpret_cast<void *>(display), &displayAttributes[0]);
    if (m_Display == EGL_NO_DISPLAY) {
        Destroy();
        return false;
    }

    // Get GLES version that was initialized with our display.
    EGLint majorVersion, minorVersion;
    if (eglInitialize(m_Display, &majorVersion, &minorVersion) == EGL_FALSE) {
        Destroy();
        return false;
    }

    // Bind OpenGL ES API for ANGLE use.
    eglBindAPI(EGL_OPENGL_ES_API);
    if (eglGetError() != EGL_SUCCESS) {
        Destroy();
        return false;
    }

    // Set our bits for each pixel.
    const EGLint configAttributes[] = {
        EGL_RED_SIZE,       (m_RedBits >= 0) ? m_RedBits : EGL_DONT_CARE,
        EGL_GREEN_SIZE,     (m_GreenBits >= 0) ? m_GreenBits : EGL_DONT_CARE,
        EGL_BLUE_SIZE,      (m_BlueBits >= 0) ? m_BlueBits : EGL_DONT_CARE,
        EGL_ALPHA_SIZE,     (m_AlphaBits >= 0) ? m_AlphaBits : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     (m_DepthBits >= 0) ? m_DepthBits : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (m_StencilBits >= 0) ? m_StencilBits : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, m_MultisamplingEnabled ? 1 : 0,
        EGL_NONE
    };

    // Choosing a config will give us a configuration "closest" to what we passed in,
    // which means it is not guaranteed to be the same. We also only want a single configuration.
    EGLint configCount;
    if (!eglChooseConfig(m_Display, configAttributes, &m_Config, 1, &configCount) || (configCount != 1)) {
        Destroy();
        return false;
    }

    // Get the actual bit values for each after choosing the configuration.
    eglGetConfigAttrib(m_Display, m_Config, EGL_RED_SIZE, &m_RedBits);
    eglGetConfigAttrib(m_Display, m_Config, EGL_GREEN_SIZE, &m_GreenBits);
    eglGetConfigAttrib(m_Display, m_Config, EGL_BLUE_SIZE, &m_BlueBits);
    eglGetConfigAttrib(m_Display, m_Config, EGL_ALPHA_SIZE, &m_AlphaBits);
    eglGetConfigAttrib(m_Display, m_Config, EGL_DEPTH_SIZE, &m_DepthBits);
    eglGetConfigAttrib(m_Display, m_Config, EGL_STENCIL_SIZE, &m_StencilBits);

    // Creates the surface for the display with the specified configuration and surface attributes.
    m_Surface = eglCreateWindowSurface(m_Display, m_Config, window, nullptr);
    if (eglGetError() != EGL_SUCCESS) {
        Destroy();
        return false;
    }

    // Set the GLES context attributes.
    std::vector<EGLint> contextAttributes;
    contextAttributes.push_back(EGL_CONTEXT_MAJOR_VERSION);
    contextAttributes.push_back(2);
    contextAttributes.push_back(EGL_CONTEXT_MINOR_VERSION);
    contextAttributes.push_back(0);
    contextAttributes.push_back(EGL_CONTEXT_OPENGL_DEBUG);
    contextAttributes.push_back(m_DebugEnabled ? EGL_TRUE : EGL_FALSE);
    contextAttributes.push_back(EGL_CONTEXT_OPENGL_NO_ERROR_KHR);
    contextAttributes.push_back(m_DisableErrors ? EGL_TRUE : EGL_FALSE);
    contextAttributes.push_back(EGL_CONTEXT_WEBGL_COMPATIBILITY_ANGLE);
    contextAttributes.push_back(EGL_TRUE);
    contextAttributes.push_back(EGL_NONE);

    // Create the context with the display, configuration and specified context attributes. 
    m_Context = eglCreateContext(m_Display, m_Config, nullptr, &contextAttributes[0]);
    if (eglGetError() != EGL_SUCCESS) {
        Destroy();
        return false;
    }

    // Lastly activate the context.
    eglMakeCurrent(m_Display, m_Surface, m_Surface, m_Context);
    if (eglGetError() != EGL_SUCCESS) {
        Destroy();
        return false;
    }

    // Allows for the creation of vertex array objects in OpenGL ES 2.0.
    const unsigned char* glExtensions = glGetString(GL_EXTENSIONS);
    if (!strstr(reinterpret_cast<const char*>(glExtensions), "GL_OES_vertex_array_object")) {
        Destroy();
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    std::cout << "[Renderer Information]" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Bits per pixel: " << m_RedBits + m_GreenBits + m_BlueBits + m_AlphaBits << std::endl;
    GLint viewportInfo[4];
    glGetIntegerv(GL_VIEWPORT, viewportInfo);
    std::cout << "Resolution: " << viewportInfo[2] << "x" << viewportInfo[3] << std::endl;
    return true;
}

void Ivy::Graphics::Renderer::Destroy(void) {
    if (m_Surface != EGL_NO_SURFACE) {
        assert(m_Display != EGL_NO_DISPLAY);
        eglDestroySurface(m_Display, m_Surface);
        m_Surface = EGL_NO_SURFACE;
    }
    if (m_Context != EGL_NO_CONTEXT) {
        assert(m_Display != EGL_NO_DISPLAY);
        eglDestroyContext(m_Display, m_Context);
        m_Context = EGL_NO_CONTEXT;
    }
    if (m_Display != EGL_NO_DISPLAY) {
        eglMakeCurrent(m_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglTerminate(m_Display);
        m_Display = EGL_NO_DISPLAY;
    }
}

bool Ivy::Graphics::Renderer::IsInitialized(void) {
    // Determines if the renderer is initialized.
    return m_Surface != EGL_NO_SURFACE &&
        m_Context != EGL_NO_CONTEXT &&
        m_Display != EGL_NO_DISPLAY;
}

void Ivy::Graphics::Renderer::SwapBuffers(void) {
    // Swaps the front and back buffer.
    eglSwapBuffers(m_Display, m_Surface);
}

void Ivy::Graphics::Renderer::SetSwapInterval(EGLint interval) {
    // For more information on swap intervals, read the following:
    // https://www.khronos.org/opengl/wiki/Swap_Interval
    eglSwapInterval(m_Display, interval);
    m_SwapInterval = interval;
}

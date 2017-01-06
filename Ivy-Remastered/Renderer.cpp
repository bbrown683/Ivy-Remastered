#include "Renderer.h"

Renderer::Renderer(EGLint GLESVersionMajor, EGLint GLESVersionMinor, EGLint red, EGLint green, EGLint blue, EGLint alpha, EGLint depth,
    EGLint stencil, bool multisample, EGLint interval, bool debug) {
    this->m_GLESVersionMajor = GLESVersionMajor;
    this->m_GLESVersionMinor = GLESVersionMinor;
    this->m_RedBits = red;
    this->m_GreenBits = green;
    this->m_BlueBits = blue;
    this->m_AlphaBits = alpha;
    this->m_DepthBits = depth;
    this->m_StencilBits = stencil;
    this->m_Multisampling = multisample;
    this->m_SwapInterval = interval;
    this->m_DebugMode = debug;
}

Renderer::~Renderer(void)
{
    Renderer::Destroy();
}

void Renderer::Clear(Color color) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(color.GetRedChannel(), color.GetGreenChannel(), color.GetBlueChannel(), color.GetAlphaChannel());
}

bool Renderer::Create(EGLNativeWindowType window, EGLNativeDisplayType display)
{
    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = reinterpret_cast<PFNEGLGETPLATFORMDISPLAYEXTPROC>(eglGetProcAddress("eglGetPlatformDisplayEXT"));
    if (!eglGetPlatformDisplayEXT) {
        Destroy();
        return false;
    }

    std::vector<EGLint> displayAttributes;
    displayAttributes.push_back(EGL_PLATFORM_ANGLE_TYPE_ANGLE);
    displayAttributes.push_back(m_Renderer);
    displayAttributes.push_back(EGL_PLATFORM_ANGLE_MAX_VERSION_MAJOR_ANGLE);
    displayAttributes.push_back(m_RendererVersionMajor);
    displayAttributes.push_back(EGL_PLATFORM_ANGLE_MAX_VERSION_MINOR_ANGLE);
    displayAttributes.push_back(m_RendererVersionMinor);

    if (m_RendererType != EGL_DONT_CARE) {
        displayAttributes.push_back(EGL_PLATFORM_ANGLE_DEVICE_TYPE_ANGLE);
        displayAttributes.push_back(m_RendererType);
    }

    if (m_RendererPresentPath != EGL_DONT_CARE) {
        const char *extensionString =
            static_cast<const char *>(eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS));
        if (strstr(extensionString, "EGL_ANGLE_experimental_present_path") == nullptr) {
            Destroy();
            return false;
        }

        displayAttributes.push_back(EGL_EXPERIMENTAL_PRESENT_PATH_ANGLE);
        displayAttributes.push_back(m_RendererPresentPath);
    }

    displayAttributes.push_back(EGL_NONE);

    m_Display = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE,
        reinterpret_cast<void *>(display),
        &displayAttributes[0]);

    if (m_Display == EGL_NO_DISPLAY) {
        Destroy();
        return false;
    }

    EGLint majorVersion, minorVersion;
    if (eglInitialize(m_Display, &majorVersion, &minorVersion) == EGL_FALSE) {
        Destroy();
        return false;
    }

    const char* displayExtensions = eglQueryString(m_Display, EGL_EXTENSIONS);

    // EGL_KHR_create_context is required to request a non-ES2 context.
    bool hasKHRCreateContext = strstr(displayExtensions, "EGL_KHR_create_context") != nullptr;
    if (majorVersion != 2 && minorVersion != 0 && !hasKHRCreateContext) {
        Destroy();
        return false;
    }

    eglBindAPI(EGL_OPENGL_ES_API);
    if (eglGetError() != EGL_SUCCESS) {
        Destroy();
        return false;
    }

    const EGLint configAttributes[] = {
        EGL_RED_SIZE,       (m_RedBits >= 0) ? m_RedBits : EGL_DONT_CARE,
        EGL_GREEN_SIZE,     (m_GreenBits >= 0) ? m_GreenBits : EGL_DONT_CARE,
        EGL_BLUE_SIZE,      (m_BlueBits >= 0) ? m_BlueBits : EGL_DONT_CARE,
        EGL_ALPHA_SIZE,     (m_AlphaBits >= 0) ? m_AlphaBits : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     (m_DepthBits >= 0) ? m_DepthBits : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (m_StencilBits >= 0) ? m_StencilBits : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, m_Multisampling ? 1 : 0,
        EGL_NONE
    };

    EGLint configCount;
    if (!eglChooseConfig(m_Display, configAttributes, &m_Config, 1, &configCount) || (configCount != 1)) {
        Destroy();
        return false;
    }

    eglGetConfigAttrib(m_Display, m_Config, EGL_RED_SIZE, &m_RedBits);
    eglGetConfigAttrib(m_Display, m_Config, EGL_GREEN_SIZE, &m_GreenBits);
    eglGetConfigAttrib(m_Display, m_Config, EGL_BLUE_SIZE, &m_BlueBits);
    eglGetConfigAttrib(m_Display, m_Config, EGL_ALPHA_SIZE, &m_AlphaBits);
    eglGetConfigAttrib(m_Display, m_Config, EGL_DEPTH_SIZE, &m_DepthBits);
    eglGetConfigAttrib(m_Display, m_Config, EGL_STENCIL_SIZE, &m_StencilBits);

    std::vector<EGLint> surfaceAttributes;
    if (strstr(displayExtensions, "EGL_NV_post_sub_buffer") != nullptr) {
        surfaceAttributes.push_back(EGL_POST_SUB_BUFFER_SUPPORTED_NV);
        surfaceAttributes.push_back(EGL_TRUE);
    }

    surfaceAttributes.push_back(EGL_NONE);

    m_Surface = eglCreateWindowSurface(m_Display, m_Config, window, &surfaceAttributes[0]);
    if (eglGetError() != EGL_SUCCESS) {
        Destroy();
        return false;
    }
    assert(m_Surface != EGL_NO_SURFACE);

    std::vector<EGLint> contextAttributes;
    if (hasKHRCreateContext) {
        contextAttributes.push_back(EGL_CONTEXT_MAJOR_VERSION_KHR);
        contextAttributes.push_back(m_GLESVersionMajor);

        contextAttributes.push_back(EGL_CONTEXT_MINOR_VERSION_KHR);
        contextAttributes.push_back(m_GLESVersionMinor);

        contextAttributes.push_back(EGL_CONTEXT_OPENGL_DEBUG);
        contextAttributes.push_back(m_DebugMode ? EGL_TRUE : EGL_FALSE);
    }
    contextAttributes.push_back(EGL_NONE);

    m_Context = eglCreateContext(m_Display, m_Config, nullptr, &contextAttributes[0]);
    if (eglGetError() != EGL_SUCCESS) {
        Destroy();
        return false;
    }

    eglMakeCurrent(m_Display, m_Surface, m_Surface, m_Context);
    if (eglGetError() != EGL_SUCCESS) {
        Destroy();
        return false;
    }

    if (m_SwapInterval != -1) {
        eglSwapInterval(m_Display, m_SwapInterval);
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;

    return true;
}

void Renderer::Destroy(void)
{
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

bool Renderer::Initialized(void) {
    return m_Surface != EGL_NO_SURFACE &&
        m_Context != EGL_NO_CONTEXT &&
        m_Display != EGL_NO_DISPLAY;
}

void Renderer::Present(void) {
    eglSwapBuffers(m_Display, m_Surface);
}

void Renderer::SetSwapInterval(EGLint interval) {
    eglSwapInterval(m_Display, interval);
    m_SwapInterval = interval;
}

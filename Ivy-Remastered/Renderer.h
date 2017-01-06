#ifndef IVY_RENDERER_H
#define IVY_RENDERER_H

#include <assert.h>
#include <vector>
#include <iostream>

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif 

#include <export.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "Symbols.h"
#include "Color.h"

class IVY_API Renderer {
public:
    Renderer(EGLint GLESVersionMajor, EGLint GLESVersionMinor, EGLint red, EGLint green, 
        EGLint blue, EGLint alpha, EGLint depth, EGLint stencil, bool multisample, 
        EGLint interval, bool debug);
    ~Renderer();

    void Clear(Color color);
    bool Create(EGLNativeWindowType window, EGLNativeDisplayType display);
    void Destroy(void);
    bool Initialized(void);
    void Present(void);

    EGLint GetRenderer(void) { return m_Renderer; };
    EGLint GetRendererType(void) { return m_RendererType; };
    EGLint GetVersionMajor(void) { return m_RendererVersionMajor; };
    EGLint GetVersionMinor(void) { return m_RendererVersionMinor; };
    
    EGLint GetGLESVersionMajor(void) { return m_GLESVersionMajor; };
    EGLint GetGLESVersionMinor(void) { return m_GLESVersionMinor; };

    EGLint GetRedBits(void) { return m_RedBits; }
    void SetRedBits(EGLint bits) { m_RedBits = bits; }
    EGLint GetGreenBits(void) { return m_GreenBits; }
    void SetGreenBits(EGLint bits) { m_GreenBits = bits; }
    EGLint GetBlueBits(void) { return m_BlueBits; }
    void SetBlueBits(EGLint bits) { m_BlueBits = bits; }
    EGLint GetAlphaBits(void) { return m_AlphaBits; }
    void SetAlphaBits(EGLint bits) { m_AlphaBits = bits; }
    EGLint GetDepthBits(void) { return m_DepthBits; }
    void SetDepthBits(EGLint bits) { m_DepthBits = bits; }
    EGLint GetStencilBits(void) { return m_StencilBits; }
    void SetStencilBits(EGLint bits) { m_StencilBits = bits; }
    bool GetVysncState(void) { return m_VsyncMode; }
    void SetVysncState(bool state) { m_VsyncMode = state; }
    EGLint GetSwapInverval(void) { return m_SwapInterval; }
    void SetSwapInterval(EGLint interval);
    
    EGLConfig GetEGLConfig(void) { return m_Config; };
    EGLDisplay GetEGLDisplay(void) { return m_Display; };
    EGLSurface GetEGLSurface(void) { return m_Surface; };
    EGLContext GetEGLContext(void) { return m_Context; };

private:

    EGLint m_Renderer               = EGL_PLATFORM_ANGLE_TYPE_DEFAULT_ANGLE;
    EGLint m_RendererType           = EGL_DONT_CARE;
    EGLint m_RendererVersionMajor   = EGL_DONT_CARE;
    EGLint m_RendererVersionMinor   = EGL_DONT_CARE;
    EGLint m_RendererPresentPath    = EGL_DONT_CARE;

    EGLint m_GLESVersionMajor;
    EGLint m_GLESVersionMinor;

    EGLint m_RedBits;
    EGLint m_GreenBits;
    EGLint m_BlueBits;
    EGLint m_AlphaBits;
    EGLint m_DepthBits;
    EGLint m_StencilBits;
    bool m_Multisampling;
    bool m_VsyncMode;
    EGLint m_SwapInterval;
    bool m_DebugMode;

    EGLConfig m_Config;
    EGLDisplay m_Display;
    EGLSurface m_Surface;
    EGLContext m_Context;
};

#endif // IVY_RENDERER_H
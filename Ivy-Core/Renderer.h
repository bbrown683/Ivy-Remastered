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

#ifndef IVY_RENDERER_H
#define IVY_RENDERER_H

#include <assert.h>
#include <vector>
#include <iostream>

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif 

#include <export.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Symbols.h"
#include "Color.h"

class IVY_API Renderer {
public:
    Renderer(EGLint redBits, EGLint greenBits, EGLint blueBits, EGLint alphaBits, EGLint depthBits, EGLint stencilBits, 
        EGLint swapIntervalbool, bool enableMultisampling, bool enableVysnc, bool enableDebug);
    ~Renderer();

    void AdjustViewport(unsigned int width, unsigned int height);
    void Clear(Color color);
    bool Create(EGLNativeWindowType window, EGLNativeDisplayType display);
    void Destroy(void);
    bool IsInitialized(void);
    void SwapBuffers(void);

    EGLint GetRenderer(void) { return m_Renderer; };
    EGLint GetRendererType(void) { return m_RendererType; };
    EGLint GetVersionMajor(void) { return m_RendererVersionMajor; };
    EGLint GetVersionMinor(void) { return m_RendererVersionMinor; };

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
    EGLint GetSwapInverval(void) { return m_SwapInterval; }
    void SetSwapInterval(EGLint interval);
    bool GetVysncState(void) { return m_VsyncEnabled; }
    void SetVysncState(bool state) { m_VsyncEnabled = state; }
    
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

    EGLint m_RedBits;
    EGLint m_GreenBits;
    EGLint m_BlueBits;
    EGLint m_AlphaBits;
    EGLint m_DepthBits;
    EGLint m_StencilBits;
    EGLint m_SwapInterval;
    bool m_MultisamplingEnabled;
    bool m_VsyncEnabled;
    bool m_DebugEnabled;

    EGLConfig m_Config;
    EGLDisplay m_Display;
    EGLSurface m_Surface;
    EGLContext m_Context;
};

#endif // IVY_RENDERER_H
#ifndef IVY_GL_H
#define IVY_GL_H

#include <export.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

static PFNGLACTIVESHADERPROGRAMPROC __glActiveShaderProgram;
#define glActiveShaderProgram __glActiveShaderProgram
static PFNGLACTIVETEXTUREPROC __glActiveTexture;
#define glActiveTexture __glActiveTexture
static PFNGLBINDATTRIBLOCATIONPROC __glBindAttribLocation;
#define glBindAttribLocation __glBindAttribLocation
static PFNGLBINDBUFFERPROC __glBindBuffer;
#define glBindBuffer __glBindBuffer
static PFNGLCLEARPROC __glClear;
#define glClear __glClear
static PFNGLCLEARCOLORPROC __glClearColor;
#define glClearColor __glClearColor
static PFNGLCOMPILESHADERPROC __glCompileShader;
#define glCompileShader __glCompileShader
static PFNGLCULLFACEPROC __glCullFace;
#define glCullFace __glCullFace
static PFNGLDRAWARRAYSPROC __glDrawArrays;
#define glDrawArrays __glDrawArrays
static PFNGLDRAWELEMENTSPROC __glDrawElements;
#define glDrawElements __glDrawElements
static PFNGLENABLEPROC __glEnable;
#define glEnable __glEnable
static PFNGLENABLEIPROC __glEnablei;
#define glEnablei __glEnablei
static PFNGLDISABLEPROC __glDisable;
#define glDisable __glDisable
static PFNGLDISABLEIPROC __glDisablei;
#define glDisablei __glDisablei
static PFNGLGENSAMPLERSPROC __glGenSamplers;
#define glGenSamplers __glGenSamplers
static PFNGLGENTEXTURESPROC __glGenTextures;
#define glGenTextures __glGenTextures
static PFNGLGETACTIVEATTRIBPROC __glGetActiveAttrib;
#define glGetActiveAttrib __glGetActiveAttrib
static PFNGLGETACTIVEUNIFORMPROC __glGetActiveUniform;
#define glGetActiveUniform __glGetActiveUniform
static PFNGLGETERRORPROC __glGetError;
#define glGetError __glGetError
static PFNGLGETINTEGERVPROC __glGetIntegerv;
#define glGetIntegerv __glGetIntegerv
static PFNGLGETPROGRAMIVPROC __glGetProgramiv;
#define glGetProgramiv __glGetProgramiv
static PFNGLGETSTRINGPROC __glGetString;
#define glGetString __glGetString
static PFNGLLINKPROGRAMPROC __glLinkProgram;
#define glLinkProgram __glLinkProgram
static PFNGLSHADERSOURCEPROC __glShaderSource;
#define glShaderSource __glShaderSource
static PFNGLTEXIMAGE2DPROC __glTexImage2D;
#define glTexImage2D __glTexImage2D
static PFNGLUNIFORM4FVPROC __glUniform4fv;
#define glUniform4fv __glUniform4fv
static PFNGLUSEPROGRAMPROC __glUseProgram;
#define glUseProgram __glUseProgram
static PFNGLVALIDATEPROGRAMPROC __glValidateProgram;
#define glValidateProgram __glValidateProgram

static void LoadGLEntryPoints() {
    glActiveShaderProgram = reinterpret_cast<PFNGLACTIVESHADERPROGRAMPROC>(eglGetProcAddress("glActiveShaderProgram"));
    glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>(eglGetProcAddress("glActiveTexture"));

    glClear = reinterpret_cast<PFNGLCLEARPROC>(eglGetProcAddress("glClear"));
    glClearColor = reinterpret_cast<PFNGLCLEARCOLORPROC>(eglGetProcAddress("glClearColor"));

    glGetIntegerv = reinterpret_cast<PFNGLGETINTEGERVPROC>(eglGetProcAddress("glGetIntegerv"));
    glGetString = reinterpret_cast<PFNGLGETSTRINGPROC>(eglGetProcAddress("glGetString"));
}

#endif // IVY_GL_H

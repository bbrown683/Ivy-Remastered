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

#include "Shader.h"

Shader::~Shader() {
    if (!m_Disposed)
        Shader::Destroy();
}

bool Shader::Create() {
    m_ShaderID = glCreateShader(m_ShaderType);
    if (m_ShaderID == GL_NO_ERROR) {
        std::cout << "Shader creation failed..." << std::endl;
        return false;
    }

    File file;
    m_ShaderSource = file.Read(m_ShaderPath);
    const char* source = m_ShaderSource.c_str();
    glShaderSource(m_ShaderID, 1, &source, nullptr);
    if (glGetError() != GL_NO_ERROR)
        std::cerr << "Failed to set source for " << m_ShaderPath << "...\n";

    glCompileShader(m_ShaderID);
    GLint compileStatus;
    glGetProgramiv(m_ShaderID, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 1) {
            std::vector<GLchar>infoLog(infoLogLength);
            glGetProgramInfoLog(m_ShaderID, static_cast<GLsizei>(infoLog.size()), nullptr, &infoLog[0]);

            std::cerr << "Shader " << m_ShaderPath << " failed to compile with error: " << &infoLog[0];
        }
        else
            std::cerr << "Shader " << m_ShaderPath << " failed to compile...";

        return false;
    }



    return true;
}

void Shader::Destroy() {
    glDeleteShader(m_ShaderID);
    m_Disposed = true;
}

GLuint Shader::GetShaderID() {
    return m_ShaderID;
}

GLenum Shader::GetShaderType() {
    return m_ShaderType;
}

std::string Shader::GetShaderPath() {
    return m_ShaderPath;
}

std::string Shader::GetShaderSource() {
    return m_ShaderSource;
}

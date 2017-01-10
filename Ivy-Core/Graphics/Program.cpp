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

#include "Program.h"

Ivy::Graphics::Program::~Program() {
    if(!m_Disposed)
        Program::Destroy();
}

bool Ivy::Graphics::Program::Create(void) {
    m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_VertexShaderID == 0 || m_FragmentShaderID == 0) {
        std::cerr << "Shader creation failed..." << std::endl;
        return false;
    }

    bool vsStatus, fsStatus;
    vsStatus = SetShaderSource(m_VertexShaderID, m_VertexShaderPath, &m_VertexShaderSource);
    fsStatus = SetShaderSource(m_FragmentShaderID, m_FragmentShaderPath, &m_FragmentShaderSource);

    if (!vsStatus || !fsStatus)
        return false;

    glCompileShader(m_VertexShaderID);
    vsStatus = ValidateShader(m_VertexShaderID);
    glCompileShader(m_FragmentShaderID);
    fsStatus = ValidateShader(m_FragmentShaderID);

    if (!vsStatus || !fsStatus)
        return false;
    
    m_ProgramID = glCreateProgram();
    if (m_ProgramID == 0) {
        std::cout << "Program creation failed..." << std::endl;
        return false;
    }

    GLenum vsError, fsError;
    glAttachShader(m_ProgramID, m_VertexShaderID);
    vsError = glGetError();
    if (vsError != GL_NO_ERROR) {
        std::cout << "Shader " << m_VertexShaderPath << " failed to attach with error: " << vsError << std::endl;
        Destroy();
        return false;
    }
    glAttachShader(m_ProgramID, m_FragmentShaderID);
    fsError = glGetError();
    if (fsError != GL_NO_ERROR) {
        std::cout << "Shader " << m_FragmentShaderPath << " failed to attach with error: " << fsError << std::endl;
        Destroy();
        return false;
    }

    // Bind the following attributes for the vertex shader slots.
    glBindAttribLocation(m_ProgramID, 0, "ivy_Position");
    glBindAttribLocation(m_ProgramID, 1, "ivy_Color0");
    glBindAttribLocation(m_ProgramID, 2, "ivy_Color1");
    glBindAttribLocation(m_ProgramID, 3, "ivy_Normal");
    glBindAttribLocation(m_ProgramID, 4, "ivy_Tangent");
    glBindAttribLocation(m_ProgramID, 5, "ivy_Bitangent");
    glBindAttribLocation(m_ProgramID, 6, "ivy_BlendWeight");
    glBindAttribLocation(m_ProgramID, 7, "ivy_BlendIndices");
    glBindAttribLocation(m_ProgramID, 8, "ivy_TexCoord0");
    glBindAttribLocation(m_ProgramID, 9, "ivy_TexCoord1");
    glBindAttribLocation(m_ProgramID, 10, "ivy_TexCoord2");
    glBindAttribLocation(m_ProgramID, 11, "ivy_TexCoord3");
    glBindAttribLocation(m_ProgramID, 12, "ivy_TexCoord4");
    glBindAttribLocation(m_ProgramID, 13, "ivy_TexCoord5");
    glBindAttribLocation(m_ProgramID, 14, "ivy_TexCoord6");
    glBindAttribLocation(m_ProgramID, 15, "ivy_TexCoord7");

    glLinkProgram(m_ProgramID);
    bool linkStatus = ValidateProgramStage(m_ProgramID, GL_LINK_STATUS);
    if (!linkStatus)
        return false;

    glValidateProgram(m_ProgramID);
    bool validateStatus = ValidateProgramStage(m_ProgramID, GL_VALIDATE_STATUS);
    if (!validateStatus)
        return false;

    glDetachShader(m_ProgramID, m_VertexShaderID);
    glDetachShader(m_ProgramID, m_FragmentShaderID);

    std::cout << "[Program Information]" << std::endl;
    std::cout << "ProgramID: " << m_ProgramID << std::endl;
    return true;
}

void Ivy::Graphics::Program::Destroy(void) {
    glDeleteShader(m_VertexShaderID);
    glDeleteShader(m_FragmentShaderID);
    glDeleteProgram(m_ProgramID);
    m_Disposed = true;
}

void Ivy::Graphics::Program::MakeActive(void) {
    glUseProgram(m_ProgramID);
}

void Ivy::Graphics::Program::MakeInactive(void) {
    glUseProgram(0);
}

bool Ivy::Graphics::Program::SetShaderSource(GLuint shaderID, std::string shaderPath, std::string* shaderSource) {
    // Read the shader and check to see if it is empty.
    // Empty signifies the file could not be found or there was no data.
    IO::File file;
    *shaderSource = file.Read(shaderPath);
    if (shaderSource->empty()) {
        Destroy();
        return false;
    }

    // Convert the std::string into an OpenGL friendly format.
    const GLchar* shaderData = shaderSource->c_str();
    glShaderSource(shaderID, 1, &shaderData, nullptr);
    if (glGetError() != GL_NO_ERROR) {
        Destroy();
        return false;
    }

    return true;
}

bool Ivy::Graphics::Program::ValidateShader(GLuint shaderID) {
    GLint compileStatus;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 1) {
            std::vector<GLchar>infoLog(infoLogLength);
            glGetShaderInfoLog(shaderID, static_cast<GLsizei>(infoLog.size()), nullptr, &infoLog[0]);

            std::cerr << "Shader Compilation Error: " << infoLog[0];
        }
        else
            std::cerr << "Shader Compilation Error...";

        Destroy();
        return false;
    }

    return true;
}

bool Ivy::Graphics::Program::ValidateProgramStage(GLuint programID, GLenum stage) {
    GLint stageStatus;
    glGetProgramiv(m_ProgramID, stage, &stageStatus);
    if (stageStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 1) {
            std::vector<GLchar>infoLog(infoLogLength);
            glGetProgramInfoLog(m_ProgramID, static_cast<GLsizei>(infoLog.size()), nullptr, &infoLog[0]);

            if(stage == GL_LINK_STATUS)
                std::cerr << "ProgramID " << m_ProgramID << " failed to link with error: " << &infoLog[0];
            else
                std::cerr << "ProgramID " << m_ProgramID << " failed to validate with error: " << &infoLog[0];
        }
        else {
            if (stage == GL_LINK_STATUS)
                std::cerr << "ProgramID " << m_ProgramID << " failed to link...";
            else
                std::cerr << "ProgramID " << m_ProgramID << " failed to validate...";
        }

        return false;
    }

    return true;
}

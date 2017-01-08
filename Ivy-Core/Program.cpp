#include "Program.h"

Program::~Program() {
    if(!m_Disposed)
        Program::Destroy();
}

bool Program::Create() {
    m_ProgramID = glCreateProgram();
    if (m_ProgramID == 0) {
        std::cout << "Program creation failed..." << std::endl;
        return false;
    }

    for each (Shader shader in m_Shaders) {
        glAttachShader(m_ProgramID, shader.GetShaderID());
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "Shader " << shader.GetShaderPath() << " failed to attach with error: " << error << std::endl;
        }
    }

    glLinkProgram(m_ProgramID);
    GLint linkStatus;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 1) {
            std::vector<GLchar>infoLog(infoLogLength);
            glGetProgramInfoLog(m_ProgramID, static_cast<GLsizei>(infoLog.size()), nullptr, &infoLog[0]);

            std::cerr << "ProgramID " << m_ProgramID << " failed to link with error: " << &infoLog[0];
        }
        else
            std::cerr << "ProgramID " << m_ProgramID << " failed to link...";

        return false;
    }

    glValidateProgram(m_ProgramID);
    GLint validateStatus;
    glGetProgramiv(m_ProgramID, GL_VALIDATE_STATUS, &validateStatus);
    if (validateStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 1) {
            std::vector<GLchar>infoLog(infoLogLength);
            glGetProgramInfoLog(m_ProgramID, static_cast<GLsizei>(infoLog.size()), nullptr, &infoLog[0]);

            std::cerr << "ProgramID " << m_ProgramID << " failed to validate with error: " << &infoLog[0];
        }
        else
            std::cerr << "ProgramID " << m_ProgramID << " failed to validate...";

        return false;
    }

    std::cout << "[Program Information]" << std::endl;
    std::cout << "ProgramID: " << m_ProgramID << std::endl;
    for each (Shader shader in m_Shaders) {
        if (shader.GetShaderType() == GL_VERTEX_SHADER)
            std::cout << "Vertex ";
        else
            std::cout << "Fragment ";
        std::cout << "Shader: " << shader.GetShaderPath() << std::endl;
    }
    return true;
}

void Program::Destroy(void) {
    for each (Shader shader in m_Shaders) {
        glDetachShader(m_ProgramID, shader.GetShaderID());
        shader.Destroy();
    }
    glDeleteProgram(m_ProgramID);
    m_Disposed = true;
}

void Program::MakeActive(void) {
    glUseProgram(m_ProgramID);
}

void Program::MakeInactive(void) {
    glUseProgram(0);
}


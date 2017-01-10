#ifndef IVY_PROGRAM_H
#define IVY_PROGRAM_H

#include <string>

#include "File.h"
#include "Renderer.h"

class IVY_API Program {
public:
    Program(std::string vertexShaderPath, std::string fragmentShaderPath) {
        this->m_VertexShaderPath = vertexShaderPath;
        this->m_FragmentShaderPath = fragmentShaderPath;
    }
    ~Program();

    bool Create(void);
    void Destroy(void);
    void MakeActive(void);
    void MakeInactive(void);

    GLuint GetProgramID(void) { return m_ProgramID; }
    
    GLuint GetVertexShaderID(void) { return m_VertexShaderID; }
    std::string GetVertexShaderPath(void) { return m_VertexShaderPath; }
    std::string GetVertexShaderSource(void) { return m_VertexShaderSource; }
    
    GLuint GetFragmentShaderID(void) { return m_FragmentShaderID; }
    std::string GetFragmentShaderPath(void) { return m_FragmentShaderPath; }
    std::string GetFragmentShaderSource(void) { return m_FragmentShaderSource; }

    
private:
    
    bool SetShaderSource(GLuint shaderID, std::string shaderPath, std::string* shaderSource);
    bool ValidateShader(GLuint shaderID);
    bool ValidateProgramStage(GLuint programID, GLenum stage);
    
    GLuint m_ProgramID;

    GLuint m_VertexShaderID;
    std::string m_VertexShaderPath;
    std::string m_VertexShaderSource;
    
    GLuint m_FragmentShaderID;
    std::string m_FragmentShaderPath;
    std::string m_FragmentShaderSource;

    bool m_Disposed;
};

#endif // IVY_PROGRAM_H
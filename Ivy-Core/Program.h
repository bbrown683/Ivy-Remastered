#ifndef IVY_PROGRAM_H
#define IVY_PROGRAM_H

#include <string>
#include <vector>

#include "Symbols.h"
#include "Shader.h"

class IVY_API Program {
public:
    Program(std::vector<Shader> shaders) {
        this->m_Shaders = shaders;
    }
    ~Program();

    bool Create(void);
    void Destroy(void);
    void MakeActive(void);
    void MakeInactive(void);

    GLuint GetProgramID(void) { return m_ProgramID; }
    std::vector<Shader> GetAttachedShaders(void) { return m_Shaders; };

private:
    
    GLuint m_ProgramID;
    std::vector<Shader> m_Shaders;

    bool m_Disposed;
};

#endif // IVY_PROGRAM_H
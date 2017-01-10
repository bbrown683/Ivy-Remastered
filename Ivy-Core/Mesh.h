#ifndef IVY_MESH_H
#define IVY_MESH_H

#include <glm/vec4.hpp>
#include <glm/matrix.hpp>

#include "Renderer.h"
#include "Program.h"

class IVY_API Mesh {
public:
    Mesh(Program& program) : m_Program(program) {}

    void Draw(void);
    
    void SetPosition(glm::vec3 position);
    void SetRotation(glm::vec3 rotation);
    void SetScale(glm::vec3 scale);

private:
    Program m_Program;

    glm::mat4 m_Position;
    glm::mat4 m_Rotation;
    glm::mat4 m_Scale;
};

#endif // IVY_MESH_H
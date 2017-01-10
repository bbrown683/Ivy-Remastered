#ifndef IVY_MODEL_H
#define IVY_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/vec4.hpp>

#include "Mesh.h"
#include "Program.h"

class IVY_API Model {
public:
    Model(Program& program) : m_Program(program) {}

    bool Load(std::string filePath);
    void Draw(void);

    glm::vec3 GetPosition(void);
    glm::vec3 GetRotation(void);
    glm::vec3 GetScale(void);

    void SetPosition(glm::vec3 position);
    void SetRotation(glm::vec3 rotation);
    void SetScale(glm::vec3 scale);

private:
    Program m_Program;
    std::string m_FilePath;
    std::vector<Mesh> m_Meshes;

    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;
};

#endif // IVY_MODEL_H
#ifndef IVY_VERTEX_H
#define IVY_VERTEX_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Symbols.h"
#include "Renderer.h"

struct IVY_API Vertex {
    glm::vec3 m_Position;
    glm::vec4 m_Color0;
    glm::vec4 m_Color1;
    glm::vec3 m_Normal;
    glm::vec3 m_Tangent;
    glm::vec3 m_Bitangent;
    glm::vec4 m_BlendWeight;
    glm::vec4 m_BlendIndices;
    glm::vec2 m_TexCoord0;
    glm::vec2 m_TexCoord1;
    glm::vec2 m_TexCoord2;
    glm::vec2 m_TexCoord3;
    glm::vec2 m_TexCoord4;
    glm::vec2 m_TexCoord5;
    glm::vec2 m_TexCoord6;
    glm::vec2 m_TexCoord7;
};

#endif // IVY_VERTEX_H

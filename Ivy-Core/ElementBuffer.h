#ifndef IVY_INDEXBUFFER_H
#define IVY_INDEXBUFFER_H

#include "Renderer.h"

class IVY_API ElementBuffer {
public:
    void Bind(void);
    void Create(void);
    void SetIndices(std::vector<GLushort> indices);
    void Unbind(void);

    void Draw(void);

private:

    GLuint m_ElementBuffer;
    std::vector<GLushort> m_Indices;
};

#endif // IVY_INDEXBUFFER_H
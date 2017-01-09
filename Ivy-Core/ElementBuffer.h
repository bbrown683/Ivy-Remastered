#ifndef IVY_INDEXBUFFER_H
#define IVY_INDEXBUFFER_H

#include "Renderer.h"

class ElementBuffer {
private:
    GLuint m_ElementBuffer;

public:
    void Bind(GLushort* indices);
    void Unbind();

    void Draw();
};

#endif // IVY_INDEX_BUFFER
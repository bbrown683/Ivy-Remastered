#ifndef IVY_VERTEXBUFFER_H
#define IVY_VERTEXBUFFER_H

#include "Renderer.h"

class VertexBuffer {
public:
    VertexBuffer(Renderer renderer) {

    }
    
    void Bind();
    void Unbind();

    void Draw();
};

#endif // IVY_VERTEXBUFFER_H
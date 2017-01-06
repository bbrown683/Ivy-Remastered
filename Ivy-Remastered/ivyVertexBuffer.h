#ifndef IVY_VERTEXBUFFER_H
#define IVY_VERTEXBUFFER_H

#include "ivyRenderer.h"

class ivyVertexBuffer {
public:
    ivyVertexBuffer(ivyRenderer renderer) {

    }
    
    void Bind();
    void Unbind();

    void Draw();
};

#endif // IVY_VERTEXBUFFER_H
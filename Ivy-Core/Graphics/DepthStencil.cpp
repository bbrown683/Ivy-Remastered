#include "DepthStencil.h"

void Ivy::Graphics::DepthStencil::State(GLenum buffer, bool flag) {
    if (buffer == GL_DEPTH_BUFFER_BIT) {
        glDepthMask(flag);
    }
    if (buffer == GL_STENCIL_BUFFER_BIT) {
        glStencilMask(flag);
    }
}

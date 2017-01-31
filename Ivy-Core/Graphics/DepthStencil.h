#ifndef IVY_DEPTHSTENCIL_H
#define IVY_DEPTHSTENCIL_H

#include "Renderer.h"

namespace Ivy {
    namespace Graphics {
        class DepthStencil {
            void State(GLenum buffer, bool flag);
        };
    }
}

#endif

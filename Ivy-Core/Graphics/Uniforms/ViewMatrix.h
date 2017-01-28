#ifndef IVY_VIEWMATRIX_H
#define IVY_VIEWMATRIX_H

#include <glm/gtc/type_ptr.hpp>

#include "../Renderer.h"

namespace Ivy {
    namespace Graphics {
        class ViewMatrix {
            GLint m_ViewLocation;
            glm::mat4 m_ViewMatrix;

        };
    }
}

#endif // IVY_VIEWMATRIX_H

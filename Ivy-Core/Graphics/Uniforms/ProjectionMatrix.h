#ifndef IVY_PROJECTIONMATRIX_H
#define IVY_PROJECTIONMATRIX_H

#include <glm/gtc/type_ptr.hpp>

#include "../Renderer.h"

namespace Ivy {
    namespace Graphics {
        class ProjectionMatrix {
            GLint m_ProjectionLocation;
            glm::mat4 m_ProjectionMatrix;

        };
    }
}

#endif // IVY_PROJECTIONMATRIX_H

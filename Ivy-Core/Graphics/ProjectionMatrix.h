#ifndef IVY_PROJECTION_MATRIX_H
#define IVY_PROJECTION_MATRIX_H

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"

namespace Ivy {
    namespace Graphics {
        class ProjectionMatrix {
            GLint m_ProjectionLocation;
            glm::mat4 m_ProjectionMatrix;

        };
    }
}

#endif // IVY_PROJECTION_MATRIX_H

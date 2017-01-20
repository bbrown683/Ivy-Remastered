#ifndef IVY_CAMERA_H
#define IVY_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>

#include "UniformBuffer.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API Camera {
        public:
            Camera(Program* program, glm::vec3 position, glm::vec3 target, float fov, unsigned int width, unsigned int height) :
                m_Program(program), m_UniformBuffer(program) {
                m_Position = position;
                m_Target = target;
                m_Fov = fov;
                m_Width = width;
                m_Height = height;
            }

            void Create();

            glm::vec3 GetCameraPosition(void) { return m_Position; }
            void SetCameraPosition(glm::vec3 position);
            glm::vec3 GetTargetPosition(void) { return m_Target; }
            void SetTargetPosition(glm::vec3 position);

        private:

            Program* m_Program;
            UniformBuffer m_UniformBuffer;

            glm::vec3 m_Position;
            glm::vec3 m_Target;
            float m_Fov;
            unsigned int m_Width;
            unsigned int m_Height;
        };
    }
}

#endif

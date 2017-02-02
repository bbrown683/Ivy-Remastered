/*
MIT License

Copyright (c) 2017 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef IVY_CAMERA_H
#define IVY_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>

#include "UniformBuffer.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API Camera {
        public:
            Camera(ShaderProgram* program, glm::vec3 position, glm::vec3 target, float fieldOfView, unsigned int width, unsigned int height, float clippingPlaneNear, float clippingPlaneFar) :
                m_Program(program), m_UniformBuffer(program) {
                m_Position = position;
                m_Target = target;
                m_FieldOfView = fieldOfView;
                m_Width = width;
                m_Height = height;
                m_ClippingPlaneNear = clippingPlaneNear;
                m_ClippingPlaneFar = clippingPlaneFar;
            }

            void Create();

            glm::vec3 GetCameraPosition(void) { return m_Position; }
            void SetCameraPosition(glm::vec3 position);
            glm::vec3 GetTargetPosition(void) { return m_Target; }
            void SetTargetPosition(glm::vec3 position);

        private:

            ShaderProgram* m_Program;
            UniformBuffer m_UniformBuffer;

            glm::vec3 m_Position;
            glm::vec3 m_Target;
            float m_FieldOfView;
            unsigned int m_Width;
            unsigned int m_Height;
            float m_ClippingPlaneNear;
            float m_ClippingPlaneFar;
        };
    }
}

#endif // IVY_CAMERA_H

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

#ifndef IVY_UNIFORMBUFFER_H
#define IVY_UNIFORMBUFFER_H

#include <glm/gtc/type_ptr.hpp>

#include "Shaders/ShaderProgram.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API UniformBuffer {
        public:
            UniformBuffer(ShaderProgram* program) : m_Program(program) {}
        
            void GetModelLocation(void);
            void GetViewLocation(void);
            void GetProjectionLocation(void);

            glm::mat4 GetModelMatrix(void);
            glm::mat4 GetViewMatrix(void);
            glm::mat4 GetProjectionMatrix(void);

            void SetModelMatrix(glm::mat4 matrix);
            void SetViewMatrix(glm::mat4 matrix);
            void SetProjectionMatrix(glm::mat4 matrix);

        private:

            ShaderProgram* m_Program;

            GLint m_ModelLocation;
            GLint m_ViewLocation;
            GLint m_ProjectionLocation;

            glm::mat4 m_ModelMatrix;
            glm::mat4 m_ViewMatrix;
            glm::mat4 m_ProjectionMatrix;
        };
    }
}

#endif // IVY_UNIFORMBUFFER_H

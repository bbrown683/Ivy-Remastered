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

#ifndef IVY_MESH_H
#define IVY_MESH_H

#include <glm/vec4.hpp>
#include <glm/matrix.hpp>

#include "Program.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API Mesh {
        public:
            Mesh(Program& program) : m_Program(program) {}

            void Draw(void);

            void SetPosition(glm::vec3 position);
            void SetRotation(glm::vec3 rotation);
            void SetScale(glm::vec3 scale);

        private:
            Program m_Program;

            glm::mat4 m_Position;
            glm::mat4 m_Rotation;
            glm::mat4 m_Scale;
        };
    }
}

#endif // IVY_MESH_H
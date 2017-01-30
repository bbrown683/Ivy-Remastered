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

#ifndef IVY_TESTMESH_H
#define IVY_TESTMESH_H

#include <glm/gtc/matrix_transform.hpp>

#include "Program.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/ElementBuffer.h"
#include "UniformBuffer.h"
#include "Texture.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API TestMesh {
        public:
            TestMesh(Program* program, std::vector<Vertex> vertices, std::vector<GLushort> indices, std::vector<Texture> textures) :
                m_Program(program), m_UniformBuffer(m_Program) {
                m_Vertices = vertices;
                m_Indices = indices;
                m_Textures = textures;
            }

            void Create(void);
            void Draw(void);

            void SetPosition(glm::vec3 position);
            void SetRotation(glm::vec3 rotation);
            void SetScale(glm::vec3 scale);

        private:
            Program* m_Program;

            std::vector<Vertex> m_Vertices;
            std::vector<GLushort> m_Indices;
            std::vector<Texture> m_Textures;

            glm::mat4 m_Translation;
            glm::mat4 m_Rotation;
            glm::mat4 m_Scale;

            VertexBuffer m_VertexBuffer;
            ElementBuffer m_ElementBuffer;
            UniformBuffer m_UniformBuffer;
        };
    }
}

#endif // IVY_TESTMESH_H
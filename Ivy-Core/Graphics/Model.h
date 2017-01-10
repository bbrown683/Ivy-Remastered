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

#ifndef IVY_MODEL_H
#define IVY_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/vec4.hpp>

#include "Mesh.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API Model {
        public:
            Model(Program& program) : m_Program(program) {}

            bool Load(std::string filePath);
            void Draw(void);

            glm::vec3 GetPosition(void);
            glm::vec3 GetRotation(void);
            glm::vec3 GetScale(void);

            void SetPosition(glm::vec3 position);
            void SetRotation(glm::vec3 rotation);
            void SetScale(glm::vec3 scale);

        private:
            Program m_Program;
            std::string m_FilePath;
            std::vector<Mesh> m_Meshes;

            glm::vec3 m_Position;
            glm::vec3 m_Rotation;
            glm::vec3 m_Scale;
        };
    }
}

#endif // IVY_MODEL_H
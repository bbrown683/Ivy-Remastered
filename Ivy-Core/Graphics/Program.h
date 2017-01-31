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

#ifndef IVY_PROGRAM_H
#define IVY_PROGRAM_H

#include <string>

#include "../IO/File.h"
#include "Renderer.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API Program {
        public:
            Program(std::string vertexShaderPath, std::string fragmentShaderPath) {
                this->m_VertexShaderPath = vertexShaderPath;
                this->m_FragmentShaderPath = fragmentShaderPath;
            }
            ~Program();

            bool Create(void);
            void Destroy(void);
            void MakeActive(void);
            void MakeInactive(void);

            GLuint GetProgramID(void) const { return m_ProgramID; }

            GLuint GetVertexShaderID(void) { return m_VertexShaderID; }
            std::string GetVertexShaderPath(void) { return m_VertexShaderPath; }
            std::string GetVertexShaderSource(void) { return m_VertexShaderSource; }

            GLuint GetFragmentShaderID(void) { return m_FragmentShaderID; }
            std::string GetFragmentShaderPath(void) { return m_FragmentShaderPath; }
            std::string GetFragmentShaderSource(void) { return m_FragmentShaderSource; }

        private:

            bool SetShaderSource(GLuint shaderID, std::string shaderPath, std::string* shaderSource);
            bool ValidateShader(GLuint shaderID);
            bool ValidateProgramStage(GLuint programID, GLenum stage);

            GLuint m_ProgramID;

            GLuint m_VertexShaderID;
            std::string m_VertexShaderPath;
            std::string m_VertexShaderSource;

            GLuint m_FragmentShaderID;
            std::string m_FragmentShaderPath;
            std::string m_FragmentShaderSource;
        };
    }
}

#endif // IVY_PROGRAM_H
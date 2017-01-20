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

#include "UniformBuffer.h"

void Ivy::Graphics::UniformBuffer::GetModelLocation(void) {
    m_ModelLocation = glGetUniformLocation(m_Program->GetProgramID(), "ivy_Model");
    if (glGetError() != GL_NO_ERROR)
        std::cerr << "Error getting model location" << std::endl;
}

void Ivy::Graphics::UniformBuffer::GetViewLocation(void) {
    m_ViewLocation = glGetUniformLocation(m_Program->GetProgramID(), "ivy_View");
    if (glGetError() != GL_NO_ERROR)
        std::cerr << "Error getting view location" << std::endl;
}

void Ivy::Graphics::UniformBuffer::GetProjectionLocation(void) {
    m_ProjectionLocation = glGetUniformLocation(m_Program->GetProgramID(), "ivy_Projection");
    if (glGetError() != GL_NO_ERROR)
        std::cerr << "Error getting projection location" << std::endl;
}

glm::mat4 Ivy::Graphics::UniformBuffer::GetModelMatrix(void) {
    return m_ModelMatrix;
}

glm::mat4 Ivy::Graphics::UniformBuffer::GetViewMatrix(void) {
    return m_ViewMatrix;
}

glm::mat4 Ivy::Graphics::UniformBuffer::GetProjectionMatrix(void) {
    return m_ProjectionMatrix;
}

void Ivy::Graphics::UniformBuffer::SetModelMatrix(glm::mat4 matrix) {
    m_ModelMatrix = matrix;
    glUniformMatrix4fv(m_ModelLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));
}

void Ivy::Graphics::UniformBuffer::SetViewMatrix(glm::mat4 matrix) {
    m_ViewMatrix = matrix;

    m_Program->MakeActive();
    glUniformMatrix4fv(m_ViewLocation, 1, GL_FALSE, glm::value_ptr(m_ViewMatrix));
    m_Program->MakeInactive();
}

void Ivy::Graphics::UniformBuffer::SetProjectionMatrix(glm::mat4 matrix) {
    m_ProjectionMatrix = matrix;
    
    m_Program->MakeActive();
    glUniformMatrix4fv(m_ProjectionLocation, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix));
    m_Program->MakeInactive();
}

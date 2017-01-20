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

#include "ElementBuffer.h"

void Ivy::Graphics::ElementBuffer::Bind(void) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
}

void Ivy::Graphics::ElementBuffer::Create(void) {
    glGenBuffers(1, &m_ElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() *
        sizeof(GLushort), reinterpret_cast<void**>(m_Indices.data()), GL_STATIC_DRAW);
}

void Ivy::Graphics::ElementBuffer::Destroy(void) {
    glDeleteBuffers(1, &m_ElementBuffer);
}

void Ivy::Graphics::ElementBuffer::SetIndices(std::vector<GLushort> indices) {
    this->m_Indices = indices;
}

void Ivy::Graphics::ElementBuffer::Unbind(void) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);
}

void Ivy::Graphics::ElementBuffer::Draw(void) {
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), 
        GL_UNSIGNED_SHORT, nullptr);
}
